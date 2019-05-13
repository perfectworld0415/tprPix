/*
 * ========================= Crawl.cpp ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.01.05
 *                                        MODIFY --
 * ----------------------------------------------------------
 *    专门管理 GameObj实例 的 位移运动
 * ----------------------------
 */
#include "Crawl.h" 

//-------------------- C --------------------//
#include <cassert>

//-------------------- CPP --------------------//
#include <vector>
#include <utility> //- pair
#include <iomanip>

//-------------------- Engine --------------------//
#include "Move.h" 
#include "SpeedLevel.h"
#include "GameObjPos.h"
#include "MapCoord.h"
#include "Collision.h"
#include "GameObj.h" 
#include "ColliEntSet.h" //- tmp

#include "esrc_time.h"
#include "esrc_chunk.h"
#include "esrc_colliEntSet.h" //- tmp


#include "debug.h" 

/*
namespace{//-------------- namespace ------------------//

    //--- 以下数据 被每一次 Crawl::RenderUpdate_2() 调用 共用 ---//
    bool isObstruct {false}; //- 碰撞检测返回值，是否检测到 "无法穿过"的碰撞
    bool isCross    {false}; //- currentMidFPos 是否进入新的 mapent

    glm::vec2 speedV {};     //- 当前帧的 速度: fpos/frame
    glm::vec2 oldMidFPos {}; //- rootAnchor 所在 mapent 的中点 的 fpos
    glm::vec2 newMidFPos {};

    MapCoord oldMCPos {};  //- rootAnchor 所在 mapent 的中点 的 mcpos
    MapCoord newMCPos {};

    MapCoord off {};  // newMCPos - oldMCPos
    NineBox  nb {};

}//------------------ namespace: end ------------------//
*/


/* ===========================================================
 *                        init
 * -----------------------------------------------------------
 */
/*
void Crawl::init(   GameObj *_goPtr, 
                    Move *_movePtr, 
                    GameObjPos *_goPosPtr, 
                    Collision *_collisionPtr  ){
    this->goPtr = _goPtr; 
    this->movePtr  = _movePtr;
    this->goPosPtr = _goPosPtr;
    this->collisionPtr = _collisionPtr;
}
*/


/* ===========================================================
 *                   RenderUpdate_2
 * -----------------------------------------------------------
 * -- 新版 crawl 位移系统。测试...
 */
/*
void Crawl::RenderUpdate_2(){

    //----------------------------//
    //  currentDirAxes & newDirAxes
    //   控制 Move/Idle 动画的切换
    //----------------------------//
    //-- skip the time without "NineBox" input --
    if( this->currentDirAxes.is_zero() && this->newDirAxes.is_zero() ){
        return;
    }
    
    //-- 在 move状态切换的 两个点 调用 OnMove() ／ OnIdle() --
    if( this->currentDirAxes.is_zero() && (this->newDirAxes.is_zero()==false) ){
        this->goPtr->actionSwitch.call_func( ActionSwitchType::Move_Move );
    }else if( (this->currentDirAxes.is_zero()==false) && this->newDirAxes.is_zero() ){
        this->goPtr->actionSwitch.call_func( ActionSwitchType::Move_Idle );
    }

    this->currentDirAxes = this->newDirAxes;
    if( this->currentDirAxes.is_zero() ){
        return; //- end_frame of one_piece_input
    }

    //----------------------------//
    // 
    //----------------------------//
    isObstruct = false; //- 碰撞检测返回值，是否检测到 "无法穿过"的碰撞
    isCross    = false; //- currentMidFPos 是否进入新的 mapent

    //--- 计算 本帧速度 ---//
    speedV = this->currentDirAxes.to_fmpos();
    speedV *= SpeedLevel_2_val(movePtr->get_speedLv()) *
              60 * esrc::timer.get_smoothDeltaTime();
                    //-- 此处计算 速度的 部分，在未来，应该被 包装起来 --

    oldMidFPos = this->goPosPtr->calc_rootAnchor_midFPos();
    newMidFPos = oldMidFPos + speedV;

    //-- 这里计算的是 rootAnchorMidFPos 的 mcpos --
    oldMCPos = fpos_2_mcpos( oldMidFPos );
    newMCPos = fpos_2_mcpos( newMidFPos );

    
    if( oldMCPos != newMCPos ){
        isCross = true;

        off = newMCPos - oldMCPos;
            assert( off.is_match_with_nineBox() ); //- 一道简陋的检测, 确保 单帧位移 不超过 周边 8 mapent
        nb.set( off.get_mpos().x, off.get_mpos().y );

        //-- 执行碰撞检测，并获知 此回合移动 是否可穿过 --
        isObstruct = this->collisionPtr->collide_for_crawl( NineBox_XY_2_Idx(nb) );        
    }

    if( isObstruct == false ){
        this->goPosPtr->accum_currentFPos_2( speedV );
        if( isCross ){
            this->goPosPtr->accum_currentMCPos_2(nb);
                        //-- 使用 NineBox 来传递参数，
                        //   决定了当前模式下的 最大速度，不能超过 1_mapent_per_frame 
                        //   想要突破这个限制，就要 进一步 完善 collision 函数
                        //   让它支持，一次检测 数个 mapent
        }
    }
    
    //---------------------------//
    //  如果确认需要位移
    //   -- 检查本go 的 新chunk，如果发生变化，释放旧chunk 中的 goids, edgeGoIds
    //       登记到 新chunk 的 goids
    //   -- 重新统计 本go 的 chunkKeys，如果确认为 临界go，  
    //       登记到 主chunk 的 edgegoids 容器中
    //---------------------------//
    Chunk   *oldChunkPtr;
    Chunk   *newChunkPtr;
    goid_t   goid = this->goPtr->id;

    chunkKey_t newChunkKey = anyMPos_2_chunkKey(  this->goPosPtr->get_currentMPos() );
                        //-- 确保在调用本函数之前，gopos 已经发生了位移
    newChunkPtr = esrc::get_chunkPtr( newChunkKey );

    if( newChunkKey!=goPtr->currentChunkKey ){
        oldChunkPtr = esrc::get_chunkPtr( this->goPtr->currentChunkKey );
        assert( oldChunkPtr->erase_from_goIds(goid) == 1 );
        oldChunkPtr->erase_from_edgeGoIds(goid);
        //---
        goPtr->currentChunkKey = newChunkKey;
        newChunkPtr->insert_2_goIds(goid);
    }

    this->goPtr->reset_chunkKeys();
    size_t chunkKeysSize = this->goPtr->get_chunkKeysRef().size();
    if( chunkKeysSize == 1 ){
        newChunkPtr->erase_from_edgeGoIds(goid);
    }else if( chunkKeysSize > 1 ){
        newChunkPtr->insert_2_edgeGoIds(goid);
    }else{
        assert(0);
    }

        //-----------------------------------------
        //-- 这个检测，最好在，所有工作都结束后，
        //   此时的结果最准确
        {//-- 打印 当前帧的 ces 区域 --- 
            IntVec2 currentMPos = this->goPtr->goPos.get_currentMPos();
            const IntVec2 compassPPos = this->goPtr->goPos.get_rootAnchorCompassPPos();
            const ColliEntHead &doCehRef = *(this->goPtr->get_rootColliEntHeadPtr());
            const ColliEntSet &doCesRef = esrc::get_colliEntSetRef( doCehRef.colliEntSetIdx ); //- get do_ces_ref
            MapCoord cesMCPos;
            cesMCPos.set_by_mpos( currentMPos - doCehRef.mposOff_from_cesLB_2_centerMPos );
            debug::clear_mapEntSlices();
            for( const auto &i : doCesRef.get_colliEnts() ){
                debug::insert_new_mapEntSlice( i+cesMCPos );
            }
        }
}
*/



/* ===========================================================
 *                   set_newCrawlDirAxes
 * -----------------------------------------------------------
 */
/*
void Crawl::set_newCrawlDirAxes( const DirAxes &_newDirAxes ){
    this->newDirAxes = _newDirAxes;

    //-- 设置 go 方向 --
    if( this->newDirAxes.get_x() < -DirAxes::threshold ){
        this->goPtr->set_direction_and_isFlipOver( GODirection::Left );

    }else if(this->newDirAxes.get_x() > DirAxes::threshold ){
        this->goPtr->set_direction_and_isFlipOver( GODirection::Right );
    }
}
*/


//namespace{//-------------- namespace ------------------//
//}//------------------ namespace: end ------------------//

