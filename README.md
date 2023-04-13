# DXGame

一个基于DX11的渲染器，用到了DirectTK库

整体步骤
------

- 实现了GameComponent-GameObject-Scene-Game、Varible-Pass-Technique-Effect-Material的层级；
- 默认着色器模型为Blinn-Phong反射模型;
  ![Jinx](./ScreenShots/BlinnPhong.gif)
- 伪天空盒(不知道FX11怎么给TextureCube绑定);
  ![Jinx](./ScreenShots/Skybox.gif)

TODOs
------

- PBR
- 完善天空盒（FX11资料太少）
