# **sunEngine** 

![sunEngineIcon](https://github.com/xiaowangxu/sunEngine/blob/master/image/sunEngine.png?raw=true)

一个由 *studio* **UNNAMED** 编写的小小的游戏框架（无用）

## 为什么
这只是在我的大学课程中为了能便利地进行一个小游戏开发，简化代码结构的绘图框架，并不是一个完整好用的游戏引擎，个人使用请注意

## 如何使用

### 0. 项目设置
在 `sunEngine_Utility.h` 中：
```c++
struct Application
{
	string Title = "TTT999 by studio UNNAMED";	// 游戏窗口标题
	Vector2<int> WindowSize = Vector2<int>(960,700);	// 弹出的窗口大小
	Vector2<GLdouble> ViewportSize = Vector2<GLdouble>(1920.0, 1400);	// 游戏画面大小
	Vector2<GLdouble> Origin = Vector2<GLdouble>(0., 0.);	// 游戏绘制原点，不必修改
	Vector3<GLclampf> BgColor = Vector3<GLclampf>(0.16f, 0.2f, 0.37f);	// 游戏背景色
	int dt = 16;	// 帧生成时间（毫秒）
};
```
### 1. 游戏编程
在 `sunEngine.cpp` 中：
```c++
// config your game setting in "sunEngine_Utility.h"
// global Mouse Plugin
// 在"sunEngine_Utility.h"中进行项目设置
// 全局鼠标插件
extern MouseObj Mouse;

// Put Your Game Object Here
// 在这里声明游戏插件或类

// Game Loop
// 游戏循环
void game_Initialize()
{
	// the script here will only run once before the game start
	// 游戏初始化
}

void game_MainLoop()
{
	// put your main game logic here
	// 游戏主循环
}
```
### 2. 插件
您只能使用插件进行绘图

目前支持的插件仅有 `Shape`

	注意插件在被构造时将被自动加入绘图列表中，因此绘制的顺序由构造顺序决定

### 3. 行为
目前只有两种行为：
+ `Animater`
+ `MouseSensor`

将行为附加到插件上：
```c++
Shape Circle;
Animater SizeChanger;

Circle.AddBehaviour(SizeChanger);
```
## 一个样例
当鼠标移动到圆上时放大，移出时缩小

在 `sunEngine.cpp` 中：
```c++
#include "pch.h"
#include "sunEngine.h"
#include "stdlib.h"
using namespace std;

// config your game setting in "sunEngine_Utility.h"
// global Mouse Plugin
// 在"sunEngine_Utility.h"中进行项目设置
// 全局鼠标插件
extern MouseObj Mouse;

// Put Your Game Object Here
// 在这里声明游戏插件或类
class GameObject
{
public:
	Shape Circle;
	Animater SizeChanger;
	MouseSensor Sensor;

	GameObject()
	{
		Circle.AddBehaviour(SizeChanger);
		Circle.AddBehaviour(Sensor);
	}
};

GameObject Object;

// Game Loop
// 游戏循环
void game_Initialize()
{
	// the script here will only run once before the game start
	// 游戏初始化
	Object.Circle.SetShape(4,1.0,1.0,1.0);
	Object.Circle.SetPosition(960,540);
	Object.Circle.SetSize(200,200);
}

void game_MainLoop()
{
	// put your main game logic here
	// 游戏主循环
	if(Object.Sensor.OnRollIn())	// MouseSensor 行为检测到鼠标移入
	{
		Object.SizeChanger.StopAnimation(bh_Animater::Current);
		Object.SizeChanger.SetAnimation(Object.Circle.GetSize().X,220,0.3,bh_Animater::BackOut,bh_Animater::Once,bh_Animater::Size);
		Object.SizeChanger.StartAnimation();
	}
	if(Object.Sensor.OnRollOut())	// MouseSensor 行为检测到鼠标移出
	{
		Object.SizeChanger.StopAnimation(bh_Animater::Current);
		Object.SizeChanger.SetAnimation(Object.Circle.GetSize().X,200,0.3,bh_Animater::BackOut,bh_Animater::Once,bh_Animater::Size);
		Object.SizeChanger.StartAnimation();
	}
}
```
## *inside* sunEngine

### 0.绘图框架的搭建

glut作为一个巨大的状态机，绘制图形的方法一般为：

``` c++{.line-numbers}
glColor3f(Color.X, Color.Y, Color.Z);		//设置当前颜色
glBegin(GL_POLYGON);						//设置状态为多边形绘制
for (int i = 0; i < PointCount; i++)		//在多边形顶点数组中循环
{
	glVertex2f(X[i],Y[i]);					//创建顶点
}
glEnd();									//设置状态为结束
```

这表明如果我们要绘制很多多边形的话我们需要手动使用上述代码，为了简化这一操作，我们先建立一个`engine_Graph`的类作为所有绘图类的基类（部分重要声明）：

``` c++{.line-numbers}
class Behaviour;		//Behaviour基类声明，因为在engine_Graph中要使用到Behaviour的引用

class engine_Graph		//绘图基类
{
private:
	Vector2<GLdouble> Position = Vector2<GLdouble>(0, 0);		//位置坐标
	GLdouble Angle = 0.0;						//角度
	Vector2<GLdouble> Size = Vector2<GLdouble>(100, 100);		//大小
	GLfloat Opacity = 1.0f;						//透明度
	sunEngine_Graph::engine_Graph_Visible Visible = sunEngine_Graph::Visible;	//可见性
	vector<Behaviour *> List;					//“Behaviour指针”的向量表
public:
	engine_Graph();			//构造
	virtual ~engine_Graph();	//虚析构

	void AddBehaviour(class Behaviour &behaviour);

	void UpdateBehaviour();		//更新成员变量中“Behaviour指针”向量表中的各个Behaviour
	virtual sunEngine_Graph::engine_Graph_AnchorPoint GetAnchorPoint() const;
	virtual void Render();		//渲染虚函数
};
```

为了完成自动渲染，即在每次刷新时为每个绘图物体自动调用`Render()`函数，在`engine_Graph.h`和`engine_Graph.cpp`中我设计了一个全局向量表：

``` c++{.line-numbers}
//全局“engine_Graph指针”向量表
extern vector<engine_Graph *> engine_Graph_Buffer;

//主渲染函数
void engine_Graph_Render()
{
	int Count = engine_Graph_Buffer.size();		//向量表维数
	if(Count == 0)								//向量表为空
	{
		App.BgColor = Vector3<GLclampf>(1.0, 0.0, 0.0);
		return;
	}
	for (int i = 0; i < Count; i++)				//向量表不为空，为每个engine_Graph指针调用Render方法
	{
		engine_Graph_Buffer.at(i)->Render();
	}
}
```
而`engine_Graph`的构造和析构函数为：

``` c++{.line-numbers}
engine_Graph::engine_Graph()		//构造函数
{
	engine_Graph_Buffer.push_back(this);		//将自己的指针加入全局向量表尾部
}

engine_Graph::~engine_Graph()
{
	int Count = engine_Graph_Buffer.size();
	for(int i = 0 ; i < Count ; i++)			//循环向量表
	{
		if(engine_Graph_Buffer.at(i) == this)	//找到自己指针的项
		{
			engine_Graph_Buffer.erase(engine_Graph_Buffer.begin()+i);	//在向量表中删除该项
		}
	}
}
```
上面就完成了一个简单的自动渲染，直接调用`engine_Graph_Render()`即可，但现在动画还不能自动执行，因此我们加入了一个`Behaviour`的概念：

* 可以将`Behaviour`施加到`engine_Graph`上
* `Behaviour`可以控制（手动或自动）`engine_Graph`的一些属性从然使其展现出一些特定行为

在`engine_BehaviourManager.h`和`engine_BehaviourManager.cpp`中,Behaviour基类的声明和定义为：

``` c++{.line-numbers}
class Behaviour
{
private:
	string Name;					//Behaviour名称
	bool Active = sunEngine_Behaviour::Active;	//是否启用
	engine_Graph *Target = NULL;			//受控的engine_Graph指针
public:
	Behaviour(const string &name = "NewBehaviour");

	void SetTarget(engine_Graph *target);
	engine_Graph *GetTarget()const;
	void SetActive(sunEngine_Behaviour::engine_Behaviour_Active &activecode);
	bool isActive()const;

	virtual ~Behaviour();
	virtual void Update(engine_Graph &target);	//Behaviour更新虚函数
};
```

在`engine_Graph.h`和`engine_Graph.cpp`中：

``` c++{.line-numbers}
void engine_Graph::AddBehaviour(Behaviour &behaviour)	//将Behaviour加入到“Behaviour指针”的向量表
{
	if(behaviour.GetTarget() != NULL)	return;		//当前Behaviour已经有Target
	this->List.push_back(&behaviour);		//当前BehaviourTarget为空，将Behaviour指针加入这个engine_Graph的Behaviour向量表中
	behaviour.SetTarget(this);			//设置当前BehaviourTarget为此engine_Graph
}

void engine_Graph::UpdateBehaviour()			//更新“Behaviour指针”向量表中的所有Behaviour
{
	for (int i = 0; i < this->List.size(); i++)	//循环“Behaviour指针”向量表
	{
		if (this->List.at(i)->isActive())		//Behaviour为启用状态
			this->List.at(i)->Update(*this);	//调用Behaviour.Update函数，将自己作为参数
	}
}
```

而`Behaviour`的自动执行可以认为是每个`engine_Graph`在被渲染之前都让`Behaviour`进行控制，在`engine_Graph.h`和`engine_Graph.cpp`中：

``` c++{.line-numbers}
void engine_Graph_Update()
{
	int Count = engine_Graph_Buffer.size();		//循环engine_Graph指针向量表
	for (int i = 0; i < Count; i++)
	{
		engine_Graph_Buffer.at(i)->UpdateBehaviour();	//调用engine_Graph.UpdateBehaviour函数
	}
}
```

### 1.游戏初始化及主循环

在`sunEngine_Utility.h`中,有一个名为`Application`的结构体和一个对应的全局实例`App`。修改结构体定义的初始值即可进行项目设置：

``` c++{.line-numbers}
struct Application
{
	string Title = "TTT999 by studio UNNAMED";	// 游戏窗口标题
	Vector2<int> WindowSize = Vector2<int>(960,700);	// 弹出的窗口大小
	Vector2<GLdouble> ViewportSize = Vector2<GLdouble>(1920.0, 1400);	// 游戏画面大小
	Vector2<GLdouble> Origin = Vector2<GLdouble>(0., 0.);	// 游戏绘制原点，不必修改
	Vector3<GLclampf> BgColor = Vector3<GLclampf>(0.16f, 0.2f, 0.37f);	// 游戏背景色
	int dt = 16;	// 帧生成时间（毫秒）
};

Application App;
```

在`sunEngine.h`中(头文件包含已省略)：

``` c++{.line-numbers}
extern Application App;		//全局App结构体

void game_Initialize();		//游戏逻辑初始化函数声明
void game_MainLoop();		//游戏主循环函数声明

int main(int argc, char *argv[])	//main函数
{
	sunEngine_Initialize(argc, argv);
	game_Initialize();
	glutDisplayFunc(&sunEngine_Render);
	glutMouseFunc(&MouseButton);
	glutMotionFunc(&MousePosition);
	glutPassiveMotionFunc(&MousePosition);
	glutReshapeFunc(&WindowResize);
	glutTimerFunc(App.dt, sunEngine_Tick, 1);
	glutMainLoop();
}
```

其中`sunEngine_Initialize(argc, argv);`对OpenGL进行初始化：

``` c++{.line-numbers}
void sunEngine_Initialize(int argc, char *argv[])	//初始化函数
{
	//glut初始化
	glutInit(&argc, argv);
	//设置显示模式
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//设置投影模式
	glMatrixMode(GL_PROJECTION);
	//设置视角和绘图位置
	gluOrtho2D(0.0, App.ViewportSize.X, 0.0, App.ViewportSize.Y);
	glViewport(0.0, 0.0, App.WindowSize.X, App.WindowSize.Y);
	//Windows窗口大小初始化
	glutInitWindowSize(App.WindowSize.X, App.WindowSize.Y);
	//创建Windows窗口
	glutCreateWindow(App.Title.data());
}
```

`game_Initialize();`运行游戏内容的初始化，在`sunEngine.cpp`中可看到具体的代码：

`glutDisplayFunc(&sunEngine_Render);`绑定渲染函数，在`glutMainLoop()`中`sunEngine_Render()`将被自动呼叫

``` c++{.line-numbers}
void sunEngine_Render(void)		//渲染函数
{
	//清除显示
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(App.BgColor.X, App.BgColor.Y, App.BgColor.Z, 1.0f);
	//上面讲到的绘制函数
	engine_Graph_Render();
	//重新显示
	glutPostRedisplay();
	//交换显存
	glutSwapBuffers();
}
```

`glutMouseFunc(&MouseButton);`
`glutMotionFunc(&MousePosition);`
`glutPassiveMotionFunc(&MousePosition);`
`glutReshapeFunc(&WindowResize);`
分别对鼠标和窗口大小改变函数进行绑定，其中的`MouseButton(), MousePosition(), MousePosition(), WindowResize()`函数实现可在`sunEngine_Utility.h/cpp`中找到。

`glutTimerFunc(App.dt, sunEngine_Tick, 1);`OpenGL定时，在经过App.dt时间后呼叫sunEngine_Tick()函数，计时器标记为1：

``` c++{.line-numbers}
void sunEngine_Tick(int dt)		//定时函数
{
	//执行游戏主循环
	game_MainLoop();
	//更新鼠标状态
	MouseUpdate();
	//上面讲到的Behaviour更新函数
	engine_Graph_Update();
	//开启下一次定时函数，保证每App.dt毫秒有一次sunEngine_Tick()调用
	glutTimerFunc(App.dt, sunEngine_Tick, 1);
}
```

`glutMainLoop();`开启OpenGL主循环。

### 2.插件和行为

在完成了上述构建后，当我们需要加入新的图像绘制插件（如图片，文本等），或是不同的行为（如动画，鼠标探测器，拖拽等），我们只需在`engine_Plugin.h/cpp`或`engine_Behaviour.h/cpp`中创建新的插件或行为，并分别公开继承自`engine_Graph`和`Behaviour`，编写对应的`Render()`和`Update()`虚函数，这样框架就会自动执行Behaviour更新和绘制了。

在当前的游戏中，我们有：

插件：
* `class Shape : public engine_Graph`

行为：
* `class Animater : public Behaviour`
* `class MouseSensor : public Behaviour`

具体功能及实现请看`engine_Plugin.h/cpp`和`engine_Behaviour.h/cpp`
