//
//========================= cube.h ==========================
//                       -- OpenGL --
//                                        创建 -- 2018.08.16
//                                        修改 -- 2018.08.16
//----------------------------------------------------------
//   立方体 顶点数据
//
//----------------------------

#ifndef _OPENGL_CUBE_TPR_H_
#define _OPENGL_CUBE_TPR_H_


/* --- 立方体。
 * -- 共36个顶点（6个面, 每个面2个三角形,  每个三角形有3个顶点.
 *    看起来很浪费，实际只有 8 个顶点。
 *    每个顶点拥有： 坐标值， uv贴图向量。
 */
float cube[] = {
    //------------- 侧 ------------------
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // G - z轴远面
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // C
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // D

     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // D
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // H
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // G

    //------------- 侧 ------------------
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // F - z轴近面
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // B
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // A

     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // A
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // E
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // F

    //------------- 侧 ------------------
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // E - x轴左面
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // H
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // F
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // E

    //------------- 侧 ------------------
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A - x轴右面
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // D
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // C

     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // C
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // B
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A

    //-------------- 底 -----------------
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G - y轴底面
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // C
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // B

     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // B
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // F
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G

    //-------------- 顶 -----------------
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // H - y轴顶面
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // D
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // E
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // H
};


//-- 立方体1 的简易版，通过 EBO 来节省数据。
float cube_1_ad[] = {
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // A
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // B
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // C
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // D

    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // E
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // F
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // G
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // H
};






/* --- 立方体 2
 * -- 共36个顶点（6个面, 每个面2个三角形,  每个三角形有3个顶点.
 *    看起来很浪费，实际只有 8 个顶点。
 *    每个顶点拥有： 坐标值， 法向量。
 */
float cube_2[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // G
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // C
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // D
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // D
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // H
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, // G

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // 
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // 
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // 
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // 
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // 
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // 

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, // 
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, // 

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, // 
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, // 

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, // 
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, // 
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, // 
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, // 

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, // 
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f  // 
};













#endif

