# 大数据技术及应用

## 一.Python语法基础

```python
写语句
	空语句
	表达式语句
	函数调用语句
	控制语句(if else switch while do...while for continue break goto)
	输入输出语句
写函数(提高代码的重用性)
写类

```

```python
顺序 选择 循环
数据结构+算法=程序
数据类型
```

### 1.Python语言基础

#### 1.1输入输出

input()结合eval()可以同时接受多个输入，多个输入之间的间隔符必须是逗号

```python
>>>a,b,c=eval(input())
1,2,3
>>>print(a,b,c)
1 2 3
```

#### 1.2控制语句

单项if语句的语法格式如下：

```python
if 布尔表达式:  #这里和java类似，只允许出现布尔表达式，和c/c++/java不一样，不需要括号单需要冒号
	语句块
```

eg：

```python
x=input("请输入用户名:")
y=input("请输入密码:")
z=input("请输入性别：(‘男’or‘女’)")
if y=="Python3.6.0":
	if z=="男":
		print("祝贺你，%s先生，你已经成功登陆！"%x)
	if z=="女":
		print("祝贺你，%s女士，你已经成功登陆！"%x)
else:
	print("对不起，密码错误，登录失败")
```

**while语句的语法**

```python
while 循环条件:
	循环体
```

**for循环语句的语法**

```python
for i in range(1,101): # 这里是一个前闭后开区间
	s+=i
print(s)
```
exp输出：5050

**for循环用于遍历元组**

有元组`tup=[(1,2),(2,3)]`
  
可以通过`for i in turple`去遍历元组

eg:判断一个数字x是否是一个素数

```python
x=119
for i in range(1,x+1): # 看作用域！！！
	if x%i==0:
		break
if i==x:
	print("Yes")
else:
	print("No")	
```

**多分支** *没有类似于`switch case`的语法结构*

```python
if 条件1:
	语句1
elif 条件2:
	语句2
elif 条件3:
	语句3
else:
	语句4 # 相当于default
```
#### 1.3对象和引用

身份：通过`id(变量名)`可以看到对象的身份

类型：通过`type(变量名)`可以看到对象的类型

值：通过`print(变量名)`可以看到对象的值

对象和引用：在Python中赋值语句总是建立变量对对象的引用，而不是复制对象给一个变量(只有在内存空间中的对象才有类型，变量的类型就是变量所引用对象的类型)

可以使用`del(变量名)`删除对一个对象的引用

#### 1.4变量

**变量名的命名规则**：和c/c++/java一致

变量支持整型、布尔、浮点、**复数** (弱类型语言)

* `int`整型：用于表示整数，`12`，`1024` etc.

* `bool`布尔型：对应两个布尔值，True和False，对应1和0

* `float`浮点型：用于表示实数，`3.14`，`1.2`，`2.5e2` etc.

* `complex`复数型：有两种表达方式，一种是`a+bj(a,b是实数)`，或者是`complex(a,b)`

**一切都是对象，无需显式定义**

* 集合类型 `set`：{1,2,3}

* 字符串类型 `str`

* 字典类型 `dict`：{"John":"18","Bob":"20"}

* 元组类型 `tuple`：(1,2,3)

* 列表类型 `list`：[1,2,3]

**运算符**

* 加法`+` 减法`-` 除法`/` 整除`//` 幂`**` 取模`%`

* 赋值运算符：`=`，`+=`，`-=`，`*=` etc

* 内置数学函数`abs(x)` `max(x,y,z)` etc

* `modf(x)`:返回整数和小数部分 `modf(3.25)=(0.25,3.0)`

**随机数**

* `choice(seq)`:从序列(列表、元组、字符串中随机挑选一个元素)

* `random`:随机生成一个[0,1)范围内的实数

* `shuffle(seq)`:将序列seq中的所有元素随机排序

* `uniform`:随机生成一个[x,y]范围内的实数

* `randint`:随机生成一个[x,y]范围内的整数

* `sample(sequence,k)`:返回一个从序列sequence中随机生成的一个长度为k的列表

**逻辑运算**

`and` `or` `not`

**关系运算**

`>` `<` `>=` `<=` `!=` `==`

**位运算**

* `&` ：按位与
* `|` ：按位或
* `^` ：按位异或
* `~` ：按位取反
* `<<` ：左移（相当于乘以2）
* `>>` ：右移（相当于整除2）

```python
>>> 5 & 3   # 101 & 011
1
>>> 5 | 3   # 101 | 011
7
>>> 5 ^ 3   # 101 ^ 011
6
>>> ~5
-6
>>> 5 << 1
10
>>> 5 >> 1
2
```

#### 1.5库的导入与扩展库的安装

常规导入：`import A as B` B是A的别名

使用from导入：`from A import B` 当存在同名包时使用这种方式导入

安装xxx模块：`pip install xxx`
 
### 2.字符串

**字符串的创建：**

单引号`''`	双引号`""`	三单引号`''''''`	三双引号`""""""`

**构造函数：**`s=str("1234")`

**转义字符：**

* 单引号里可以有双引号，不需要转译

* str3=r"Hello\nworld"可以让转义字符不生效

定义字符集：`bstr4=str4.encode('utf-8')`

**输出函数**：(类似c++)

`file=open(filename,mode,encoding)`

`print("内容",file="")`

**字符串的方法**：

* `len()`函数可以返回字符串的长度

* `s[index]`可以访问字符串s中下表为`index`的字符

eg：

```python
s="Hello,World"
for i in range(0,len(s)):
	print(s[i],end="-")
```

* 切片操作`sname[start:end:step]`从字符串中截取部分字符并组成新的字符串(索引号为负数则是从最后开始往前截取)

eg:

```python
sname="学习python使我快乐"
print(sname[:]) #全部缺省，输出全部
print(sname[3:8]) #输出ython，前闭后开，索引号从0开始
```

eg:九九乘法表
```c++
#include<stdio.h>
int main()
{
    for(int i=1;i<=9;++i)
    {
        for(int j=i;j<=9;++j)
        {
            printf("%d*%d=%d\t",i,j,i*j);
        }
        printf("\n");
    }
    return 0;
}
```
```python
for i in range(1,10):
    for j in range(i,10):
        print("%d*%d=%d\t"%(i,j,i*j),end=" ")
    print(" ")
```

**格式化输出**

三种格式化方式：

* `%`占位符格式化（类似C语言的printf）：

```python
name="Tom"; age=18; score=87.5
print("我是%s，今年%d岁，成绩%.1f分" % (name, age, score))
# 预期输出：我是Tom，今年18岁，成绩87.5分
```

* `str.format()`方法（用`{}`作为占位符）：

```python
print("我是{0}，今年{1}岁".format(name, age))            # 按位置
print("我是{name}，今年{age}岁".format(name="Tom", age=18))  # 按关键字
```

* f-string（Python3.6新增，最简洁）：

```python
print(f"我是{name}，今年{age}岁")
# 预期输出：我是Tom，今年18岁
```

**常用方法**

* `s.upper()` / `s.lower()` ：全部转大写 / 全部转小写
* `s.strip()` ：去除字符串两端的空白（`lstrip`/`rstrip`分别去除左/右）
* `s.split("分隔符")` ：按分隔符拆分返回列表；`"连接符".join(列表)` 把列表拼接成字符串
* `s.replace(old, new)` ：替换子串
* `s.find(sub)` ：返回子串首次出现的索引，不存在返回-1（`rfind`从右向左查找）
* `s.startswith(prefix)` / `s.endswith(suffix)` ：判断前缀 / 后缀
* `s.isdigit()` / `s.isalpha()` ：判断是否全是数字 / 字母
* `s.count(sub)` ：统计子串出现次数

```python
s="  Python is powerful  "
print(s.strip())                  # 预期输出：Python is powerful
print(s.strip().split(" "))       # 预期输出：['Python', 'is', 'powerful']
print("-".join(["a","b","c"]))    # 预期输出：a-b-c
print(s.replace("powerful","strong"))  # 预期输出：  Python is strong  
print(s.find("Python"))           # 预期输出：2
```

### 3.列表

#### **创建列表**：

* 列表写在方括号之间，列表中的类型可以不同，可以欧数字、字符串、字典、集合等数据类型

* 将字符串转换为一个列表`list2=list('chemistry') #将字符串转换为列表`

* 在列表后面增加元素`y=y+[8]`,相当于是将两个列表连接起来

#### 常用方法

- Python 列表对象的常用方法

##### 1. 添加元素

- `list.append(x)` ：在末尾添加 `x`

- `list.insert(i, x)` ：在索引 `i` 处插入 `x`

- `list.extend(iterable)` ：扩展列表

##### 2. 删除元素

- `list.remove(x)` ：删除第一个 `x`

- `list.pop(i=-1)` ：删除并返回索引 `i` 处元素

- `del list[i]` ：删除索引 `i` 处元素

- `list.clear()` ：清空列表

##### 3. 查找元素

- `list.index(x, start, end)` ：返回 `x` 的索引

- `list.count(x)` ：统计 `x` 出现次数

- `x in list` ：检查 `x` 是否存在

##### 4. 排序和反转

- `list.sort(key=None, reverse=False)` ：原地排序

- `list.reverse()` ：反转列表

- `sorted(list, key=None, reverse=False)` ：返回新排序列表

##### 5. 复制列表

- `list.copy()` ：浅拷贝

- `list[:]` ：切片复制

- `import copy; copy.deepcopy(list)` ：深拷贝

##### 6. 其他常用方法

- `len(list)` ：获取长度

- `sum(list)` ：求和

- `max(list)` / `min(list)` ：获取最大/最小值

- `list.count(x)` ：统计 `x` 次数

- `list * n` ：重复列表 `n` 次

#### 列表推导/生成式

`[2*x for x in a]`

eg:
```python
x=[1,2,3,4,5,6,7,8,9,10]
y=[x**2 for i in x]
print(y)
# 预期输出：[1,4,9,16,25,36,49,64,81,100]
y=[x**2 for i in x if i%2==0]
# 预期输出：[4,16,36,64,100]，筛选操作
```

#### 列表排序

`sorted([list],[迭代参数])`

eg:`sorted([46,15,-12,9,-21,30],key=abs) #按照绝对值大小进行排序`

### 4.集合

集合是无序、元素不重复的序列，用`{}`或`set()`创建（注意：空集合必须用`set()`，因为`{}`表示空字典）。

* 创建：`s={1,2,3}`、`set([1,2,3,3])`（自动去重）
* 添加：`s.add(x)`
* 删除：`s.remove(x)`（不存在会报错）/ `s.discard(x)`（不存在不报错）/ `s.pop()`（随机删除一个元素）
* 集合运算：并集`s1 | s2`或`s1.union(s2)`、交集`s1 & s2`或`s1.intersection(s2)`、差集`s1 - s2`或`s1.difference(s2)`、对称差集`s1 ^ s2`
* 成员判断：`x in s`
* 集合推导式：`{x**2 for x in range(5)}`

```python
s1={1,2,3}; s2={2,3,4}
print(s1 | s2)   # 预期输出：{1, 2, 3, 4}
print(s1 & s2)   # 预期输出：{2, 3}
print(s1 - s2)   # 预期输出：{1}
print(1 in s1)   # 预期输出：True

s=set("hello")
print(s)         # 预期输出：{'h', 'e', 'l', 'o'}（去重且无序）
```

### 5.元组

元组是不可变的序列，创建后不能增删改元素，用圆括号表示。

* 创建：`t=(1,2,3)`；单元素元组必须加逗号：`t=(1,)`
* 支持索引和切片，与列表相同
* 元组解包（拆包）：`a,b,c=t`
* 元组只有两个方法：`t.index(x)`、`t.count(x)`
* 与列表互转：`list(t)`、`tuple(lst)`
* 元组vs列表：元组不可变，可以作为字典的键，占内存更小、访问速度更快

```python
t=(1,2,3)
a,b,c=t
print(a,b,c)        # 预期输出：1 2 3
print(t[1:])        # 预期输出：(2, 3)
print(list(t))      # 预期输出：[1, 2, 3]

# 元组可以作为字典的键（列表不行）
d={(1,2):"坐标"}
print(d[(1,2)])     # 预期输出：坐标
```

### 6.字典

字典是"键-值对"（key-value）的无序可变序列，用`{}`或`dict()`创建。键必须是不可变类型且不能重复。

* 创建：`d={"name":"Tom","age":18}`、`dict(name="Tom", age=18)`
* 访问：`d[key]`（键不存在会报错）/ `d.get(key, 默认值)`（键不存在返回默认值，不报错）
* 修改/添加：`d[key]=value`（键存在则修改，不存在则添加）
* 删除：`del d[key]`、`d.pop(key)`（删除并返回该键的值）、`d.clear()`（清空）
* 常用方法：`d.keys()`、`d.values()`、`d.items()`、`d.update(d2)`（合并另一个字典）
* 遍历：`for k in d`（遍历键）、`for k,v in d.items()`（遍历键值对）
* 字典推导式：`{k:v for k,v in d.items() if 条件}`

```python
d={"name":"Tom","age":18}
print(d["name"])        # 预期输出：Tom
print(d.get("sex","男"))  # 预期输出：男（键不存在时取默认值）
d["score"]=87           # 添加新键
for k,v in d.items():
    print(k,v)
# 预期输出：name Tom / age 18 / score 87

scores={"Math":90,"English":87,"Python":95}
print([k for k,v in scores.items() if v>=90])  # 预期输出：['Math', 'Python']
```

### 7.程序流程控制

程序的三种基本控制结构：顺序结构、选择结构、循环结构（对应本节开头"顺序 选择 循环"）。

* 顺序结构：从上到下逐条执行
* 选择结构：`if/elif/else`判断；条件表达式（三目运算符）`a if 条件 else b`
* 循环结构：`while 条件:`与`for i in range(...):`
* `break`：跳出整个循环；`continue`：跳过本次循环继续下一次；`pass`：空语句占位
* 循环的`else`子句：循环正常结束（没有被break打断）时才执行
* `enumerate(序列)`：同时获得下标和元素

```python
# 求1~100的偶数和（演示continue）
s=0
for i in range(1,101):
    if i%2==1:
        continue
    s+=i
print(s)   # 预期输出：2550

# 循环else子句：循环正常结束才执行
for i in range(1,6):
    if i==10:
        break
else:
    print("循环正常结束")   # 预期输出：循环正常结束

# enumerate同时获取下标和值
for idx,val in enumerate(["a","b","c"]):
    print(idx,val)
# 预期输出：0 a / 1 b / 2 c

# 条件表达式（三目运算符）
x=5
print("偶数" if x%2==0 else "奇数")   # 预期输出：奇数
```

### 8.函数

eg：
```python
def add(a,b):
	return a+b
print(add(3,5)) #类似于c，除了没有类型外

def swap(a,b):
	a,b=b,a #无法实现交换的功能

def swapp(a,b):
	return b,a
m,n=swapp(3,5)
print(m,n) #预期输出：5 3
```

#### 定义函数

**Python允许嵌套定义**函数，即在一个函数中定义了另一个函数。内层函数可以访问外层函数中定义的变量，但是不能重新赋值，内层函数的局部命名空间不能包含外层函数定义的变量

#### Python函数参数的类型

**位置参数**

```python
functionName(参数1,参数2):
	语句：
```

**默认值参数**

```python
def person(name,age,sex):
	语句
person(age=18,sex='M',name=John) #以关键字的形式调用函数
```

**可变长度参数**

```python
def fun(*args,**kwargs): #args能接受所有的位置参数，kwargs可以接受所有的关键字参数(以字典的方式输出)
	for i in args:
		print(i)
	for j in kwargs:
		print(j)
fun(1,2,3,4,name:3,age:4) # 预期输出：1 2 3 4 name age
```

**函数实参**

**表现形式**：关键字参数、序列解包参数

```python
def f(a, b, c):
    return a + b + c

print(f(1, 2, 3))              # 位置参数      预期输出：6
print(f(b=2, a=1, c=3))        # 关键字参数（与顺序无关）预期输出：6
print(f(*[1, 2, 3]))           # 序列解包：把列表拆成位置实参  预期输出：6
print(f(**{"a": 1, "b": 2, "c": 3}))  # 字典解包：把字典拆成关键字实参  预期输出：6
```

#### lambda表达式
```python
f=lambda x,y,z:x+y+z # 类似于c++/java inline，c语言的宏
```

**labmda表达式匿名函数和def函数的区别**:def创建的函数是有名称的，而lambda是匿名的

**变量的作用域**：在一个源代码文件中，在函数之外定义的变量成为全局变量，作用域(范围)为其所在的源代码文件(Java抛弃了全局变量，慎用、少用全局变量)；局部变量、块变量

如果要在函数内访问全局变量，可以使用`global 变量名`声明全局变量

#### 常用内置函数

##### `map(func,swq1[,seq2,...])`第一个参数接受一个函数名，后面的参数接受一个或者多个可迭代的序列，将func作用在

```python
a=[1,2,3,4]
def square(x):
	return x**2
b=map(square,a)
print(list(b)) # 如果这里不写list(b)，python解释器会输出b的地址
```

##### `reduce(function,sequence[,initializer])`

```python
from functools import reduce
reduce(add,[1,2,3,4,5]) # 计算元素之和
```

##### `filter(func,iterable)`函数

```python
def is_odd(n):
	return n%2==1

newlist=filter(is_odd,[1,2,3,4,5])
print(list(newlist))
```

#### 装饰器（包装）

- 应用场景：

```python
def func(a,b):
	return a+b

def debug(func):
	def wrapper():
		print("[DEBUG]:enter{}()".format(func.__name__))
		return func()
	return wrapper

@debug
def say_hello():
	print("Hello!")

say_hello()
```

代码解释

```python
# 定义一个函数 func，它接收两个参数 a 和 b，并返回它们的和
def func(a, b):
    return a + b

# 定义一个装饰器函数 debug
def debug(func):
    # 在装饰器内部定义一个包装函数 wrapper
    def wrapper():
        # 在函数执行前打印调试信息，显示被装饰的函数名称
        print("[DEBUG]: enter {}()".format(func.__name__))
        # 调用被装饰的函数 func
        return func()  # ⚠️ 这里有问题，func 可能需要参数，但 wrapper 没有传递任何参数
    return wrapper  # 返回 wrapper 这个包装函数

# 使用 @debug 语法糖（相当于 say_hello = debug(say_hello)）
@debug
def say_hello():
    print("Hello!")

# 调用 say_hello()，实际上执行的是 debug 装饰器内的 wrapper() 函数
say_hello()
```
### 9.文件与文件夹操作

**打开文件**

```python
f=open("a.txt","r",encoding="utf-8")   # 打开文件，返回文件对象
f.close()                              # 使用完必须关闭文件
```

* mode参数：
  - `"r"`只读（默认）、`"w"`只写（覆盖原内容）、`"a"`追加
  - `"rb"`/`"wb"`二进制模式（图片、视频等文件）
  - `"r+"`/`"w+"`读写模式

* 读文件：`f.read()`读全部、`f.readline()`读一行、`f.readlines()`读所有行返回列表
* 写文件：`f.write(s)`、`f.writelines(列表)`
* 推荐使用`with...as`语句，可自动关闭文件：

```python
with open("data.txt","w",encoding="utf-8") as f:
    f.write("第一行\n")
    f.write("第二行\n")

with open("data.txt","r",encoding="utf-8") as f:
    for line in f:               # 逐行读取
        print(line.strip())
# 预期输出：第一行 / 第二行
```

**os模块（文件夹操作）**

* `os.getcwd()` 获取当前工作目录
* `os.listdir(path)` 列出目录下所有文件和文件夹
* `os.mkdir(path)` 创建文件夹、`os.rmdir(path)` 删除空文件夹
* `os.remove(file)` 删除文件、`os.rename(旧名,新名)` 重命名
* `os.path.exists(path)` 判断文件或目录是否存在
* `os.path.join(a,b)` 拼接路径（自动处理不同系统的分隔符）
* `os.walk(path)` 递归遍历目录，每次返回(当前目录, 子目录列表, 文件列表)

```python
import os
print(os.getcwd())              # 当前工作目录
print(os.listdir("."))          # 当前目录下的文件和文件夹
os.mkdir("mydir")               # 创建文件夹mydir
print(os.path.exists("mydir"))  # 预期输出：True
```

**扩展**：`pathlib`模块提供更现代的路径操作，如`from pathlib import Path; Path("a/b").exists()`。

### 10.面向对象程序设计

- 特性：封装、继承、多态

#### 面向对象的程序设计

- 一个类中通常包含一个特殊的函数`__init__`，作为类的构造函数

- 一个类中的函数都有self参数，类似于c++和java的this指针，例如定义矩形周长
```python
class Rectangle:
	def __init__(self,width1,height1): # 构造函数
		self.width=width1
		self.height=height1
	def getPerimeten(self): # 用于返回矩形的周长
		return 2*(self.width+self.height)
```

- 类方法
```python
@classmethod
def 方法名(cls)
```
- 静态方法
```python
@staticmethod
def 方法名([形参数列表])
```

- 析构函数
```python
def __del__(self)
```

**继承**：子类继承父类的属性和方法，用`class 子类(父类)`定义：

```python
class Animal:
    def __init__(self,name):
        self.name=name
    def speak(self):
        print("动物叫")

class Dog(Animal):
    def __init__(self,name):
        super().__init__(name)   # 调用父类的构造函数
    def speak(self):             # 方法重写（覆盖父类方法）
        print("汪汪汪")

d=Dog("旺财")
d.speak()          # 预期输出：汪汪汪
print(d.name)      # 预期输出：旺财（继承了父类的属性）
```

**多态**：同一个方法在不同对象上有不同的表现。Python是"鸭子类型"——不关心对象的类型，只要对象有该方法即可调用：

```python
class Cat(Animal):
    def speak(self):
        print("喵喵喵")

for a in [Dog("旺财"), Cat("咪咪")]:
    a.speak()
# 预期输出：汪汪汪 / 喵喵喵
```

**私有成员**：Python没有真正的私有成员。双下划线`__x`会被"名称改写"为`_类名__x`，起到私有作用；单下划线`_x`只是一种约定，表示"内部使用"：

```python
class Person:
    def __init__(self,name,age):
        self.name=name
        self.__age=age       # 私有属性，外部不能直接访问
    def getAge(self):
        return self.__age

p=Person("Tom",18)
print(p.name)       # 预期输出：Tom
# print(p.__age)    # 报错：AttributeError
print(p.getAge())   # 预期输出：18
```

**属性装饰器`@property`**：把方法当作属性一样访问，常用于"只读"属性：

```python
class Circle:
    def __init__(self,r):
        self.r=r
    @property
    def area(self):
        return 3.14*self.r**2

c=Circle(2)
print(c.area)    # 预期输出：12.56（像属性一样调用，不加括号）
```

**类型判断**：`isinstance(对象, 类型)`判断对象是否属于某个类型（可处理继承关系），`hasattr(对象, "属性名")`判断对象是否有某属性。

### 11.模块和包

* 模块：一个`.py`文件就是一个模块，可以被其他程序导入复用
* 包：包含`__init__.py`文件的文件夹，用于组织管理多个相关的模块

**导入方式**：

```python
import math                    # 导入整个模块
import math as m               # 导入模块并起别名（简化书写）
from math import sqrt, pi      # 从模块中导入指定函数
from math import *             # 导入所有内容（不推荐，容易命名冲突）
```

**`if __name__ == "__main__":`**：模块被直接运行时`__name__`的值为`"__main__"`；被别的程序导入时为模块名。把测试代码放在该语句下，可以做到"既能直接运行，也能被导入而不执行测试代码"：

```python
def add(a,b):
    return a+b

if __name__ == "__main__":
    print(add(3,5))    # 只有直接运行本文件时才执行，导入时不执行
```

**常用标准库**：

* `math`：数学函数，`math.sqrt(9)`、`math.pi`、`math.pow(2,3)`
* `random`：随机数，`random.randint(1,100)`、`random.choice(列表)`、`random.shuffle(列表)`
* `datetime`：日期时间，`datetime.datetime.now()`、`now.strftime("%Y-%m-%d")`
* `os`/`sys`：操作系统接口 / 解释器相关（如`sys.argv`获取命令行参数）

**第三方库安装**：`pip install 包名`（安装）、`pip list`（查看已安装包）、`pip uninstall 包名`（卸载）。本课程使用的numpy、pandas、matplotlib、scikit-learn等都属于第三方库。

### 12.错误和异常处理

异常（Exception）：程序运行过程中出现的错误会抛出异常，如果不处理，程序会终止退出。使用`try/except`捕获并处理异常：

```python
try:
    n=int(input("请输入一个整数："))
    print(100/n)
except ValueError:                 # 捕获特定类型异常（输入非数字）
    print("输入的不是整数")
except ZeroDivisionError:          # 除零异常
    print("除数不能为0")
except Exception as e:             # 捕获其他所有异常（Exception是所有异常的父类）
    print("发生异常：",e)
else:
    print("没有异常时才执行")        # try块成功执行完才运行
finally:
    print("无论是否异常都会执行")    # 常用于关闭文件、释放资源
```

**常见异常类型**：`ValueError`（值错误）、`TypeError`（类型错误）、`IndexError`（下标越界）、`KeyError`（字典键不存在）、`NameError`（变量未定义）、`FileNotFoundError`（文件不存在）、`ZeroDivisionError`（除零错误）

**主动抛出异常**：用`raise`语句主动抛出一个异常：

```python
def set_age(age):
    if age<0 or age>150:
        raise ValueError("年龄不合法")   # 主动抛出异常
    return age
```

**断言**：`assert 条件, "提示信息"`，条件为False时抛出`AssertionError`，常用于调试阶段校验假设。

**文件异常处理**：`try/except`可以包裹文件操作代码，配合`finally`（或`with`自动关闭）保证文件资源被正确释放。

### 13.Tkinter图形用户界面设计

Tkinter是Python自带的GUI（图形用户界面）库，无需额外安装，导入方式：`import tkinter as tk`。

**基本流程**：创建主窗口 → 创建组件 → 布局 → 进入消息循环

```python
import tkinter as tk

root=tk.Tk()                      # 创建主窗口
root.title("我的程序")             # 设置窗口标题
root.geometry("300x200")          # 设置窗口大小（宽x高）

label=tk.Label(root,text="请输入用户名：")   # 标签组件
label.pack()

entry=tk.Entry(root)              # 单行输入框组件
entry.pack()

label2=tk.Label(root,text="")     # 用于显示结果的标签
label2.pack()

def show():
    label2.config(text="你好，"+entry.get())   # 回调函数：读取输入框内容

button=tk.Button(root,text="确定",command=show)  # command绑定事件回调函数
button.pack()

root.mainloop()                   # 进入消息循环（窗口保持显示）
```

**常用组件**：`Label`标签、`Button`按钮、`Entry`单行输入框、`Text`多行文本框、`Listbox`列表框、`Radiobutton`单选按钮、`Checkbutton`复选按钮

**布局方式**：`pack()`按顺序摆放、`grid()`网格布局（`grid(row=0, column=0)`指定行列位置）

### 14.数据可视化

数据可视化：用图形（图表）直观地展示数据，帮助发现数据中的规律、趋势和异常。

**常用图表类型**：

* 折线图（plot）：展示数据随时间的变化趋势
* 柱状图（bar）：对比不同类别的数值大小
* 饼图（pie）：展示各部分占整体的比例
* 散点图（scatter）：观察两个变量之间的相关关系
* 直方图（hist）：查看数据的分布情况
* 箱线图（boxplot）：查看数据分布并识别异常值

**常用可视化库**：

* matplotlib：最基础、最通用的绘图库
* seaborn：基于matplotlib，统计图形更美观、简洁
* pyecharts：百度ECharts的Python接口，输出交互式HTML网页图表

（详细内容见第五章"Matplotlib、seaborn、pyecharts数据可视化基础"）

**最小示例（matplotlib画正弦曲线）**：

```python
import numpy as np
import matplotlib.pyplot as plt

x=np.linspace(0,2*np.pi,100)
y=np.sin(x)
plt.plot(x,y)
plt.title("sin曲线")      # 图表标题
plt.xlabel("x")           # x轴标签
plt.ylabel("sin(x)")      # y轴标签
plt.show()
```

### 15.数据库编程

Python内置`sqlite3`模块，无需安装即可操作SQLite数据库。SQLite是一种轻量级嵌入式数据库，数据保存在单个文件中，适合中小型应用。

**基本流程**：连接数据库 → 获取游标 → 执行SQL → 提交事务 → 关闭连接

```python
import sqlite3

conn=sqlite3.connect("student.db")     # 连接数据库（文件不存在会自动创建）
cur=conn.cursor()                      # 获取游标

# 建表：IF NOT EXISTS表示表已存在时不重复创建
cur.execute("CREATE TABLE IF NOT EXISTS stu(id INTEGER PRIMARY KEY, name TEXT, score REAL)")

# 增（?是占位符，用于防止SQL注入）
cur.execute("INSERT INTO stu(name,score) VALUES(?,?)",("Tom",87.5))
# 删
cur.execute("DELETE FROM stu WHERE name=?",("Tom",))
# 改
cur.execute("UPDATE stu SET score=? WHERE name=?",(90,"Tom"))
# 查
cur.execute("SELECT * FROM stu")
rows=cur.fetchall()                    # 返回所有记录（列表套元组）
print(rows)

conn.commit()                          # 提交事务（增删改之后必须commit才生效）
cur.close()                            # 关闭游标
conn.close()                           # 关闭连接
```

**与pandas结合**：

* `pd.read_sql("SELECT * FROM stu", conn)`：把SQL查询结果直接变成DataFrame
* `df.to_sql("表名", conn, if_exists="replace")`：把DataFrame写入数据库表（配合`sqlalchemy`引擎使用）

## 二.NumPy数值计算基础

(和SciPy一起对表matlab，高数、微积分、线性代数、概率、优化)

### 1.掌握NumPy数组对象ndarray

```python
>>> a=[1,2]
>>> 2*a
[1, 2, 1, 2]
>>> import numpy
>>> a=numpy.array([1,2]) # 调用构造函数
>>> print(a)
[1 2]
>>> print(2*a) # 对数组对象进行运算
[2 4]
```

#### 1.创建数组之前了解数组的基本属性

- ndim 返回int，表示数组的维数

- shape 返回tuple，表示数组形状的阵列，对于n行m列的矩阵，形状为(n,m)

- size 返回int，表示数组元素的总数，数组形状的乘积

- dtype 返回data-type，表示数组中元素的类型

- itemsize 返回int，表示每个元素的大小

#### 2.数组创建

函数签名：

```python
numpy.array(object, dtype=None, *, copy=True, order='K', subok=False, ndmin=0, like=None)
```

生成等差数列

```python
numpy.linspace(0,1,100) # 在0到1之间生成100个x，如果第三个参数缺省，则默认为50
```

生成等比数列

```python
numpy.logspace(start,stop,num=50)
```

其他特殊的数组

- zeros函数，创建值全部为0的数组

- eye函数，生成主对角线上全部为1的单位矩阵

- diag函数，创建类似对角的数组，即除对角线外其他元素均为0

- ones函数，创建一个元素全部为1的数组

#### 3.生成随机数

#### 4.变换数组形态

```python
numpy.reshape(a,newshape,order='C')
# 改变形状时不改变原始数据的值
# 如果修改后的大小和原大小不符合，抛出异常
```

```python
>>> d=numpy.arange(1,13)
>>> e=d.reshape((4,3))
>>> print(e)
[[ 1  2  3]
 [ 4  5  6]
 [ 7  8  9]
 [10 11 12]]
 >>> f=d.reshape((3,4))
>>> print(f)
[[ 1  2  3  4]
 [ 5  6  7  8]
 [ 9 10 11 12]]
 >>> d.shape=(3,4) 
 #修改属性和reshape的区别，reshape是形成一个新的数组，但是修改属性实在原数组上的修改
>>> print(d)
[[ 1  2  3  4]
 [ 5  6  7  8]
 [ 9 10 11 12]]
```

### 2.掌握NumPy矩阵与通用函数

#### 常见属性

| 属性 | 描述 |
|------|------|
| `T`  | 返回自身的转置 |
| `H`  | 返回自身的共轭转置 |
| `I`  | 返回自身的逆矩阵 |
| `A`  | 返回自身数据的二维数组的一个视图（没有做任何的复制） |

#### ndarray的基本索引和切片

一位数组的索引：与Python的列表索引功能相似

多维数组的索引：

- arr[r1:r2,c1:c2]

- arr[1,1] 等价arr[1][1]

- [:]代表某个维度的数据 / 表示所有的维度都要

```python
import numpy as np
import matplotlib.pyplot as plt
data=2*np.random.rand(10000,2)-1
x=data[:,0]
y=data[:,1]
idx=x**2+y**2<1
hole=x**2+y**2<0.5
idx=np.logical_and(idx,~hole)
plt.plot(x[idx],y[idx],'go',markersize=1)
plt.show()
```

### 3.利用NumPy进行统计分析

**生成随机数组**（衔接前面"生成随机数"小节）：

```python
import numpy as np
a=np.random.randn(3,4)                    # 标准正态分布（均值0标准差1）的3行4列数组
b=np.random.randint(1,10,size=(2,5))      # [1,10)范围内的随机整数
c=np.random.normal(0,1,100)               # 正态分布：均值为0、标准差为1，共100个
```

**常用统计函数**：

* `np.mean(a)` 均值、`np.median(a)` 中位数（两者差异反映数据分布的偏斜程度）
* `np.sum(a)` 求和、`np.ptp(a)` 极差（最大值-最小值）
* `np.std(a)` 标准差、`np.var(a)` 方差（注意：numpy默认按总体计算，除n；pandas的`std`默认按样本计算，除n-1）
* `np.min(a)` / `np.max(a)` 最小值/最大值
* `np.percentile(a, q)` 百分位数，如`np.percentile(a, 25)`即下四分位数

**axis参数**：`axis=0`按列统计、`axis=1`按行统计（不指定则对全部元素统计）：

```python
a=np.arange(12).reshape(3,4)
print(a.mean())            # 全部元素的均值  预期输出：5.5
print(a.mean(axis=0))      # 每列的均值     预期输出：[4. 5. 6. 7.]
print(a.sum(axis=1))       # 每行的和       预期输出：[ 6 22 38]
```

**累计求和**：`np.cumsum(a)`返回前缀和组成的数组：

```python
print(np.cumsum(np.array([1,2,3])))   # 预期输出：[1 3 6]
```

**相关分析**（研究两个变量之间的线性关系）：

* 协方差`np.cov(x, y)`：协方差>0正相关、<0负相关
* 相关系数`np.corrcoef(x, y)`：r∈[-1,1]，|r|越接近1线性关系越强，r>0正相关、r<0负相关

```python
x=np.array([1,2,3,4,5])
y=np.array([2,4,6,8,10])        # 完全正相关
print(np.corrcoef(x,y))
# 预期输出：[[1. 1.]
#           [1. 1.]]
```

**直方图统计**：`np.histogram(a, bins=10)`把数据分成10个区间，返回(频数数组, 区间边界数组)。

**综合示例**（对随机数据的统计描述）：

```python
data=np.random.normal(50,10,1000)    # 均值50、标准差10的1000个数据
print("均值：", round(data.mean(),2))
print("标准差：", round(data.std(),2))
print("中位数：", np.median(data))
print("25%分位数：", np.percentile(data,25))
# 预期输出：均值在50附近、标准差在10附近，中位数与均值接近（正态分布较对称）
```

## 三.pandas统计分析基础

* 背景：在c/c++语言中，一般采用结构体保存csv、xlsx文件,类似于MySQL的增删改查

* (只了解数据处理、数据分析和数据可视化)

### 1.认识pandas库
- 1.数据读写：csv,excel,sql

- 2.数据清洗(省略)

- 3.数据转换(map、apply、applymap、pipe)

- 4.合并于拼接

- 5.数据分析(基本统计量、分组聚合)

- 6.数据的可视化

```python
import pandas as pd
pd.set_option("display.width",100)
musicdata=pd.read_table("./daa/musicdata.csv",sep=",",encoding="gbk") # 返回值是dataframe类型
print(len(musicdata))
print(type(musicdata))
```

### 2.构造函数

```python
import numpy as np
import pandas as pd
df = pd.DataFrame(
    data=np.arange(12).reshape((4, 3)),
    index=list("ABCD"),
    columns=["aa", "bb", "cc"]
)
print(df)

print(df.describe()) # 数据摘要

print(df.T) # 输出转置

df["dd"]=12 # 增加一列dd，设置为12
print(df)

df.drop("A",inplace=True) # 如果不设置inplace，返回值不会被接收,df数组不会被修改
print(df)

print(np.min(df["aa"])) # 用np做最小值
print(np.var(df["aa"])) # 用np做方差
print(np.std(df["aa"])) # 用np做标准差

print(df["aa"].describe) # 对某一列进行描述

s=pd.Series([1,1,1,1,2,2,2,3,3,3,34,4,4,4,4])
print(s.value_counts()) # 统计频数

x.info() # 查看字段的类型

x["year"]=x["date"].dt.year
x["day"]=x["date"].dt.day # 计算域：这一项的数值由其他项计算而来
print(x)
x["gap"]=x["date"]-x["date"].min()
print(x)

m=pd.date_range("2025-2-1","2025-3-1") #使用python生成时间序列
print(m)
```

预期输出
```
   aa  bb  cc
A   0   1   2
B   3   4   5
C   6   7   8
D   9  10  11
             aa         bb         cc
count  4.000000   4.000000   4.000000
mean   4.500000   5.500000   6.500000  # mean统计的是平均值
std    3.872983   3.872983   3.872983  # 标准差
min    0.000000   1.000000   2.000000
25%    2.250000   3.250000   4.250000  # 25百分位数
50%    4.500000   5.500000   6.500000  # 50百分位数
75%    6.750000   7.750000   8.750000
max    9.000000  10.000000  11.000000
```

### 3.透视表和交叉表

**透视表** `pd.pivot_table(df, values=统计列, index=行分组列, columns=列分组列, aggfunc=聚合函数, margins=True, fill_value=0)`：对数据进行分组聚合后再重新排列展示，类似于Excel中的透视表功能。

* `values`：需要统计的数值列
* `index`：按哪一列（或哪几列）分组，作为行
* `columns`：按哪一列分组，作为列
* `aggfunc`：聚合函数，默认`np.mean`，可选`np.sum`/`np.count`等（可传列表同时计算多种统计量）
* `margins=True`：增加合计行/合计列
* `fill_value`：无数据的位置用指定值填充

```python
import numpy as np
import pandas as pd

df=pd.DataFrame({
    "姓名":["张三","李四","王五","张三","李四","王五"],
    "部门":["销售","销售","技术","技术","销售","技术"],
    "销售额":[100,150,120,90,180,130]
})
print(pd.pivot_table(df, values="销售额", index="姓名", columns="部门",
                     aggfunc=np.sum, margins=True))
# 预期输出：
# 部门    技术   销售  All
# 姓名
# 张三   90.0 100.0  190
# 李四    NaN 330.0  330
# 王五  250.0   NaN  250
# All   340.0 430.0  770
```

**交叉表** `pd.crosstab(index=行变量, columns=列变量, margins=True)`：专门用于统计两个分类变量的频数（相当于"计数"版的透视表）：

```python
print(pd.crosstab(df["姓名"], df["部门"], margins=True))
# 预期输出：
# 部门  技术  销售  All
# 姓名
# 张三    1    1    2
# 李四    0    2    2
# 王五    2    0    2
# All     3    3    6
```

**分箱** `pd.cut(series, bins=[...], labels=[...])`：把连续型数据划分成若干个区间（离散化），常与`value_counts()`结合统计各区间频数：

```python
s=pd.Series([55,65,75,85,90,95])
cut=pd.cut(s, bins=[0,60,70,80,100], labels=["不及格","及格","良好","优秀"])
print(cut.value_counts())
# 预期输出：
# 优秀      3
# 良好      1
# 及格      1
# 不及格    1
```

## 四.使用pandas进行数据预处理

### 1.合并数据

**轴向拼接** `pd.concat([df1, df2, ...], axis=0, ignore_index=True)`：

* `axis=0`（默认）纵向拼接：多行合并，要求列名一致
* `axis=1`横向拼接：多列合并，按索引对齐左右拼接
* `ignore_index=True`：重新生成连续的行索引（不保留原索引）

```python
import pandas as pd

df1=pd.DataFrame({"学号":[1,2],"姓名":["张三","李四"]})
df2=pd.DataFrame({"学号":[3,4],"姓名":["王五","赵六"]})
print(pd.concat([df1,df2], ignore_index=True))
# 预期输出：
#    学号  姓名
# 0     1   张三
# 1     2   李四
# 2     3   王五
# 3     4   赵六
```

**表合并** `pd.merge(df1, df2, on=公共键, how="inner", suffixes=("_x","_y"))`，类似SQL中的JOIN：

* `how="inner"`（默认）内连接：只保留两表都匹配得上的记录
* `how="left"`左连接：保留左表的全部记录，右表无匹配则填NaN
* `how="right"`右连接：保留右表的全部记录
* `how="outer"`外连接：保留两表的全部记录
* `suffixes`：两表相同列名的后缀，避免列名冲突

```python
score=pd.DataFrame({"学号":[1,2,3],"成绩":[87,92,78]})
info =pd.DataFrame({"学号":[2,3,4],"班级":["一班","二班","三班"]})
print(pd.merge(score, info, on="学号", how="left"))
# 预期输出（左连接：学号1在info中无匹配，班级为NaN）：
#    学号   成绩   班级
# 0     1    87   NaN
# 1     2    92   一班
# 2     3    78   二班
print(pd.merge(score, info, on="学号", how="outer"))
# 预期输出：上述3行之外，还会多出学号4的一行（成绩为NaN）
```

**索引连接**：`df1.join(df2)`按索引进行合并。

### 2.清洗数据

**缺失值处理**：原始数据中空缺的部分用`NaN`表示。

* 检测：`df.isnull()`返回布尔表；`df.isnull().sum()`统计每列的缺失个数
* 删除：`df.dropna()`默认删除含缺失值的行；参数`subset=["列名"]`指定只检查某些列，`how="all"`表示整行全为空才删除
* 填充：`df.fillna(值)`用固定值填充（`df.fillna(df.mean())`用各列均值、`df.fillna(df.median())`用中位数）；`method="ffill"`用上一行的值填充，`method="bfill"`用下一行的值填充
* 插值：`df.interpolate()`用线性插值填补缺失值（时间序列数据常用）

```python
import pandas as pd
import numpy as np

df=pd.DataFrame({"A":[1,2,np.nan,4],"B":[5,np.nan,7,9]})
print(df.isnull().sum())
# 预期输出：A    1 / B    1
print(df.fillna({"A":0, "B":df["B"].mean()}))
# 预期输出：A的NaN填成0；B的NaN填成B列均值7.0（(5+7+9)/3）
```

**重复值处理**：

* `df.duplicated()`标记重复行（返回布尔Series）
* `df.drop_duplicates()`删除重复行，默认保留第一条（`keep="last"`保留最后一条，`subset=["列"]`按指定列判断重复）

```python
df2=pd.DataFrame({"学号":[1,1,2],"成绩":[80,80,90]})
print(df2.drop_duplicates())
# 预期输出：只保留（学号1，成绩80）和（学号2，成绩90）两行，重复的一行被删除
```

**异常值处理**（明显偏离正常范围的数据）：

* 方法1：基于描述统计——低于/高于某个分位数视为异常
* 方法2：3σ原则——数据近似服从正态分布时，超出`均值±3*标准差`范围的样本视为异常值，删除或替换为上下界
* 方法3：箱线图法（IQR）——小于`Q1-1.5*IQR`或大于`Q3+1.5*IQR`视为异常（其中IQR=Q3-Q1）。箱线图法不受极端值影响，更稳健：

```python
data=pd.Series([10,12,11,13,12,11,100])     # 100是异常值
q1=data.quantile(0.25); q3=data.quantile(0.75)
iqr=q3-q1
lower=q1-1.5*iqr; upper=q3+1.5*iqr
print(data[(data>=lower)&(data<=upper)])
# 预期输出：10,12,11,13,12,11 这6个正常值；100超出上界被判定为异常值
```

### 3.标准化数据

**为什么需要标准化**：不同特征的量纲和数值范围差异很大（如年龄0~100、年收入0~100万），数值大的特征会主导距离计算和模型训练。标准化把所有特征拉到同一个尺度上，让模型公平对待每个特征。

**1. 离差标准化（Min-Max）**：把数据映射到[0,1]区间，适合数据有明确上下界的情况

公式：`x' = (x - min) / (max - min)`

```python
import numpy as np

a=np.array([10,20,30,40,50])
norm=(a-a.min())/(a.max()-a.min())
print(norm)
# 预期输出：[0.   0.25 0.5  0.75 1.  ]
```

**2. 标准差标准化（Z-score）**：结果为均值为0、标准差为1的分布，适合数据近似正态分布的情况，是最常用的标准化方法

公式：`x' = (x - mean) / std`

```python
zs=(a-a.mean())/a.std()
print(zs)
# 预期输出：均值为0、标准差为1的一组标准值
```

**3. 小数定标标准化**：通过移动小数点位置消除量级差异

公式：`x' = x / 10^k`（k取使得|x'|max<1的最小整数）

**sklearn实现**（实际建模时推荐使用，详见第六章）：

```python
from sklearn.preprocessing import MinMaxScaler, StandardScaler

X=np.array([[1.,2.],[3.,4.],[5.,6.]])
print(MinMaxScaler().fit_transform(X))     # 每列分别做离差标准化
print(StandardScaler().fit_transform(X))   # 每列分别做Z-score标准化
# 注意：先fit(X_train)再用同一个scaler去transform(X_test)，
# 不能用测试集重新fit，否则会泄漏测试集信息
```

### 4.转换数据

三种函数变换方法（对应第三章"数据转换"的功能）：

* `map`：对Series的每个元素执行函数变换（一对一）
* `apply`：作用于Series的每个元素，或DataFrame的每行/每列（`axis=1`按行、`axis=0`按列）
* `applymap`：对DataFrame的每一个元素执行变换

```python
import pandas as pd
import numpy as np

df=pd.DataFrame({"工资":[5000,7000,9000]})
df["工资_千元"]=df["工资"].map(lambda x: round(x/1000,1))
print(df)
# 预期输出：
#     工资  工资_千元
# 0  5000     5.0
# 1  7000     7.0
# 2  9000     9.0

df2=pd.DataFrame({"a":[1,2],"b":[3,4]})
print(df2.apply(np.sum, axis=1))        # 每行求和 预期输出：0    4 / 1    6
print(df2.applymap(lambda x: x*10))     # 每个元素乘以10
```

**哑变量处理（one-hot编码）** `pd.get_dummies(df, columns=[列名])`：把类别型（字符串）特征转换为多列0/1数值列，供机器学习模型使用：

```python
df3=pd.DataFrame({"性别":["男","女","男"],"成绩":[80,90,85]})
print(pd.get_dummies(df3, columns=["性别"]))
# 预期输出：
#    成绩  性别_女  性别_男
# 0   80      0      1
# 1   90      1      0
# 2   85      0      1
```

**时间序列转换** `pd.to_datetime`：把字符串列转成日期时间类型，再用`.dt`提取年份、月份等成分：

```python
s=pd.Series(["2025-03-01","2025-06-15"])
t=pd.to_datetime(s)
print(t.dt.year)      # 预期输出：0    2025 / 1    2025
print(t.dt.month)     # 预期输出：0    3 / 1    6
```

**重命名与排序**：

```python
df4=pd.DataFrame({"name":["Tom","Jerry"],"score":[80,95]})
df4=df4.rename(columns={"name":"姓名","score":"成绩"})     # 列名重命名
print(df4.sort_values("成绩", ascending=False))            # 按成绩降序排列
# 预期输出：Jerry(95) 在前，Tom(80) 在后
```

## 五.Matplotlib、seaborn、pyecharts数据可视化基础

### 1.Matplotlib

Matplotlib是Python最基础、最常用的绘图库，绘图功能全面，通过`pyplot`子模块使用。

**基本绘图流程**：

```python
import matplotlib.pyplot as plt
import numpy as np

x=np.linspace(0,2*np.pi,100)   # 在[0,2π]之间生成100个点
y=np.sin(x)
plt.plot(x,y)                   # 绘制折线图
plt.xlabel("x")                 # x轴标签
plt.ylabel("sin(x)")            # y轴标签
plt.title("正弦曲线")            # 图表标题
plt.show()                      # 显示图形
```

**解决中文乱码**（Windows环境下默认字体不支持中文）：

```python
plt.rcParams["font.sans-serif"]=["SimHei"]   # 设置中文字体为黑体
plt.rcParams["axes.unicode_minus"]=False     # 正常显示负号
```

**常用图形**：

* 折线图 `plt.plot(x,y)`：展示数据随时间变化的趋势
* 散点图 `plt.scatter(x,y)`：观察两个变量的相关关系
* 柱状图 `plt.bar(cat,val)`：对比不同类别的数值大小
* 饼图 `plt.pie(values,labels=labels)`：展示各部分占比
* 直方图 `plt.hist(data,bins=10)`：查看数据分布

**多子图**：`plt.subplot(2,2,1)`把画布分成2行2列，第三个参数1表示在第1个子图位置绘图。

**保存图片**：`plt.savefig("a.png")`（必须在`plt.show()`之前调用）。

### 2.seaborn

seaborn基于matplotlib，专门用于统计绘图，代码更简洁、图形更美观。数据一般直接传入pandas的DataFrame或Series。

```python
import seaborn as sns

sns.set_style("whitegrid")   # 设置绘图风格
```

**常用图形**：

* `sns.histplot(df["列"])` ：单变量分布直方图
* `sns.boxplot(x="类别列", y="数值列", data=df)` ：箱线图（观察分组分布与异常值）
* `sns.heatmap(df.corr(), annot=True)` ：相关性热力图（annot=True显示数值）
* `sns.pairplot(df)` ：多变量两两关系图（对角线为分布，其余为散点）
* `sns.countplot(x="类别列", data=df)` ：类别频数柱状图

**示例（相关性热力图）**：

```python
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df=pd.DataFrame({"身高":[170,175,180,165],"体重":[65,70,75,55],"运动量":[3,5,8,1]})
sns.heatmap(df.corr(), annot=True, cmap="coolwarm")
plt.show()
```

### 3.pyecharts

pyecharts是Python调用百度ECharts的接口，输出交互式HTML网页图表（可鼠标悬停、缩放、联动），适合Web端展示。

```python
from pyecharts.charts import Bar, Pie

# 柱状图
bar=Bar()
bar.add_xaxis(["一月","二月","三月"])
bar.add_yaxis("销售额",[100,150,120])
bar.set_global_opts(title_opts={"text":"月度销售额"})   # 设置标题
bar.render("bar.html")        # 渲染为HTML文件，浏览器打开查看

# 饼图：数据为[(名称, 数值), ...]格式
pie=Pie()
pie.add("占比", [("苹果",30),("香蕉",20),("梨",50)])
pie.render("pie.html")
```

pyecharts v2.x采用链式对象调用：先创建图表对象，再`add`系列数据、`set_global_opts`设置标题等全局配置，最后`render()`输出HTML文件。

## 六.使用scikit-learn构建模型

scikit-learn（简称sklearn）是Python最常用的机器学习库。所有模型统一为"三步走"接口：

1. `model=类名(超参数)` 创建模型对象
2. `model.fit(X_train, y_train)` 训练模型（学习参数）
3. `model.predict(X_test)` 预测、`model.score(X_test, y_test)` 评估

**数据集划分** `train_test_split`：

```python
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
```

* `test_size`：测试集比例（0.2表示20%用于测试）
* `random_state`：随机种子，固定后每次划分结果一致，保证实验可复现

**特征标准化**：先`fit_transform`训练集，再只`transform`测试集（防止数据泄漏）：

```python
from sklearn.preprocessing import StandardScaler

scaler=StandardScaler()
X_train=scaler.fit_transform(X_train)
X_test=scaler.transform(X_test)
```

**常用模型**：

* 线性回归 `LinearRegression`：回归基础模型，属性`coef_`为系数、`intercept_`为截距
* 岭回归 `Ridge(alpha=1.0)`：加了L2正则，缓解多重共线性与过拟合
* 逻辑回归 `LogisticRegression()`：二分类（尽管名字带"回归"）
* K近邻 `KNeighborsClassifier(n_neighbors=5)`：分类
* 决策树 `DecisionTreeClassifier(max_depth=3)`：分类，可解释性强
* 随机森林 `RandomForestClassifier(n_estimators=100)`：分类，多棵决策树投票
* KMeans `KMeans(n_clusters=3)`：无监督聚类

**模型评估**：

* 分类：准确率`accuracy_score`、混淆矩阵`confusion_matrix`、分类报告`classification_report`（含精确率/召回率/F1）
* 回归：均方误差`mean_squared_error`（越小越好）、R²决定系数`r2_score`（越接近1越好）

**交叉验证** `cross_val_score(model, X, y, cv=5)`：把数据分成5份，轮流用4份训练、1份验证，返回5个分数，取均值更可靠地评估模型泛化能力。

**完整案例（鸢尾花分类）**：

```python
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report

iris=load_iris()
X, y=iris.data, iris.target
X_train, X_test, y_train, y_test=train_test_split(X, y, test_size=0.3, random_state=42)

knn=KNeighborsClassifier(n_neighbors=3)
knn.fit(X_train, y_train)
print(knn.score(X_test, y_test))      # 准确率，预期输出：1.0 左右
print(classification_report(y_test, knn.predict(X_test)))
```

## 七.竞赛网站用户行为分析

**案例背景与目标**：获取某竞赛网站的用户访问日志（含用户ID、访问时间、访问页面等字段），通过分析用户访问规律，为内容运营和活动推送提供依据。

**1. 数据读取与探索**：

```python
import pandas as pd

df=pd.read_csv("./data/user_action.csv",encoding="utf-8")
print(df.head())          # 查看前5行，了解字段
print(df.info())          # 查看字段类型和缺失情况
print(df.describe())      # 数值列统计摘要
```

* 典型字段：`user_id`用户ID、`page`访问页面、`time`访问时间（字符串类型）
* `df.isnull().sum()`查看每列缺失值数量

**2. 数据清洗**：

```python
df=df.drop_duplicates()                 # 去重（重复点击产生的冗余日志）
df=df.dropna(subset=["user_id","time"]) # 删除关键字段缺失的行
df["time"]=pd.to_datetime(df["time"])   # 时间字符串转为日期时间类型
```

**3. 用户活跃度分析（分组统计）**：

```python
print(df["user_id"].value_counts().head(10))   # Top10活跃用户
df["hour"]=df["time"].dt.hour                  # 提取小时
hour_count=df.groupby("hour").size()           # 统计每个小时的访问量
print(hour_count)
```

**4. 可视化**：

```python
import matplotlib.pyplot as plt
plt.rcParams["font.sans-serif"]=["SimHei"]
plt.rcParams["axes.unicode_minus"]=False

hour_count.plot(kind="bar")     # 各小时访问量柱状图
plt.title("用户访问时段分布")
plt.xlabel("小时")
plt.ylabel("访问次数")
plt.show()
```

**5. 分析结论**：

* 若访问高峰集中在某个时段（如19-22点），说明用户群体以学生/上班族为主，推送与活动应安排在该时段
* 结合`page`字段统计各页面访问量，找出最受欢迎的板块，指导内容运营
* 本项目体现数据分析标准流程：**数据获取 → 数据清洗 → 探索分析 → 可视化 → 业务结论**

## 八.企业所得税预测分析

**案例背景与目标**：根据企业的多个经营特征（营业收入、成本费用、资产总额、从业人数等）预测其应缴纳的所得税额——典型的**回归问题**。

**1. 数据读取与探索**：

```python
import pandas as pd

df=pd.read_csv("./data/tax.csv",encoding="utf-8")
print(df.head())
print(df.info())
# 特征列：营业收入、营业成本、利润总额、资产总额、从业人数……
# 标签列（目标）：所得税额
```

**2. 数据准备**：

```python
from sklearn.model_selection import train_test_split

X=df.drop("所得税", axis=1)      # 特征矩阵（去掉标签列）
y=df["所得税"]                    # 标签
X_train, X_test, y_train, y_test=train_test_split(X, y, test_size=0.2, random_state=42)
```

**3. 建模与评估（线性回归 vs 岭回归）**：

```python
from sklearn.linear_model import LinearRegression, Ridge
from sklearn.metrics import mean_squared_error, r2_score

model=LinearRegression()
model.fit(X_train, y_train)
y_pred=model.predict(X_test)
print("MSE：", mean_squared_error(y_test, y_pred))   # 均方误差，越小越好
print("R²：", r2_score(y_test, y_pred))              # R²越接近1拟合效果越好

ridge=Ridge(alpha=1.0)             # 岭回归缓解多重共线性
ridge.fit(X_train, y_train)
print("Ridge R²：", r2_score(y_test, ridge.predict(X_test)))
```

**4. 结果解释**：

```python
print(list(zip(X.columns, model.coef_)))   # 各特征对应的回归系数
```

* 系数绝对值越大，该特征对所得税的影响越大；系数为正表示正相关
* 若特征之间存在较强相关性（如营业收入与利润总额），线性回归系数可能不稳定，应优先考虑岭回归
* 可用matplotlib画"预测值-真实值"散点图，点越靠近y=x直线说明预测越准

## 九.餐饮企业客户流失预测

**案例背景与目标**：根据餐饮客户的历史消费数据（月均消费金额、消费频次、最近一次消费距今天数等），预测客户未来是否会流失——典型的**二分类问题**。

**1. 数据读取与探索**：

```python
import pandas as pd

df=pd.read_csv("./data/customer.csv",encoding="utf-8")
print(df.head())
print(df["是否流失"].value_counts())   # 类别分布（1=流失，0=未流失）
# 特征建议：月均消费金额、月均消费次数、平均客单价、最近一次消费距今天数、会员时长等
```

**2. 流失与未流失客户特征对比**：

```python
import seaborn as sns
import matplotlib.pyplot as plt

sns.boxplot(x="是否流失", y="月均消费金额", data=df)   # 箱线图对比
plt.show()
# 若流失客户的箱线整体偏低，说明低消费客户更容易流失
```

**3. 建模（逻辑回归 vs 随机森林）**：

```python
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

X=df.drop("是否流失", axis=1)
y=df["是否流失"]
X_train, X_test, y_train, y_test=train_test_split(X, y, test_size=0.2, random_state=42)

lr=LogisticRegression(max_iter=1000)
lr.fit(X_train, y_train)
print("逻辑回归准确率：", accuracy_score(y_test, lr.predict(X_test)))
print(confusion_matrix(y_test, lr.predict(X_test)))
print(classification_report(y_test, lr.predict(X_test)))

rf=RandomForestClassifier(n_estimators=100, random_state=42)
rf.fit(X_train, y_train)
print("随机森林准确率：", rf.score(X_test, y_test))
# 注意：流失预测中召回率(recall)更重要——目标是尽量找出真正会流失的客户
```

**4. 特征重要性分析（随机森林）**：

```python
print(sorted(zip(X.columns, rf.feature_importances_), key=lambda x:-x[1]))
```

* 最近一次消费距今天数（RFM模型中的R）通常是最重要的流失预警指标
* 业务建议：对高流失风险客户（消费频次低、距上次消费时间长）提前发送优惠券、电话回访，降低流失率

## 十.导数、梯度、Jacobian、Hessian

**1. 导数**

* 定义：f'(x)=lim(Δx→0)[f(x+Δx)-f(x)]/Δx，表示函数在x处的瞬时变化率
* 几何意义：曲线上该点切线的斜率
* 常用求导公式：(xⁿ)'=nxⁿ⁻¹、(sinx)'=cosx、(eˣ)'=eˣ、(lnx)'=1/x
* 运算法则：和差法则(u±v)'=u'±v'；乘积法则(uv)'=u'v+uv'；链式法则[f(g(x))]'=f'(g(x))·g'(x)

**2. 偏导数**

* 多元函数对某一个变量求导时，把其余变量视为常数，得到的结果即偏导数 ∂f/∂x

**3. 梯度（Gradient）**

* 定义：梯度是一个向量 ∇f=(∂f/∂x₁, ∂f/∂x₂, ..., ∂f/∂xₙ)，由函数对所有变量的偏导数组成
* 意义：梯度方向是函数值增长最快的方向，负梯度方向是函数值下降最快的方向
* **梯度下降法**（机器学习训练模型的核心）：
  - 参数更新公式：`w_new = w_old - η·∇f`，其中η为学习率（步长）
  - η太小收敛慢，η太大会震荡甚至发散；实践中常用随机梯度下降SGD、批量梯度下降等变体
* 例：f(x,y)=x²+y²，则∇f=(2x, 2y)，在点(1,1)处梯度为(2,2)，沿负梯度方向(-2,-2)可走向最低点(0,0)

**4. Jacobian矩阵**

* 定义：向量值函数 f:Rⁿ→Rᵐ（输出是m维向量）的一阶偏导数组成的 m×n 矩阵
* 意义：反映自变量发生微小变化时，每个输出分量如何变化（m个输出 × n个输入）
* 例：f(x,y)=(x+y, x·y)，则J=[[1, 1], [y, x]]

**5. Hessian矩阵**

* 定义：多元标量函数的二阶偏导数组成的 n×n 对称方阵
* 用途：判断极值点性质——Hessian正定→极小值点，负定→极大值点，不定→鞍点
* 牛顿法使用Hessian（或其近似）加速优化收敛；但变量n很大时计算Hessian代价极高，深度学习更常用一阶的梯度下降

**6. 与机器学习的关系**

* 线性回归等模型通过`w = w - η·∇L(w)`更新参数：代价函数L对参数w求梯度，指导参数沿下降方向迭代
* 神经网络的反向传播（BP）本质上是链式法则+梯度计算
* 梯度下降沿负梯度方向迭代，最终收敛到代价函数的（局部）最小值

**7. Python示例（用sympy求导）**：

```python
import sympy as sp

x, y=sp.symbols("x y")
f=x**2+y**2
print(sp.diff(f, x))        # ∂f/∂x  预期输出：2*x
print(sp.diff(f, y))        # ∂f/∂y  预期输出：2*y
# 梯度向量即为 (2x, 2y)

H=sp.hessian(f, [x, y])     # Hessian矩阵
print(H)                    # 预期输出：Matrix([[2, 0], [0, 2]])，正定→(0,0)是极小值点
```

## 最后的课程论文

**选题建议**（结合本课程所学，完成一个完整的数据分析/挖掘项目）：

* 数据来源：公开数据集——Kaggle、阿里天池、和鲸社区、国家统计局官网等
* 课题方向：电商用户行为分析、房价预测、销售预测、股票数据可视化、文本评论情感分析等

**论文结构（参考）**：

* 摘要：研究目的、数据与方法、主要结论（300字左右）
* 引言/背景：问题背景与研究意义
* 数据说明：数据来源、字段含义、数据规模
* 方法：数据预处理、建模方法（回归/分类/聚类）
* 实验与结果分析：评估指标、图表（matplotlib/seaborn/pyecharts）
* 结论与展望：业务建议、不足与改进方向

**写作要求**：代码、图表与文字分析相结合，严格按照下面的"数据挖掘流程"展开，重点突出结果解释与应用价值。

## *

完整的数据挖掘流程（与国际标准流程CRISP-DM对应）如下：

1. 问题定义
   明确业务目标，把业务问题转化为数据问题，确定问题类型（回归/分类/聚类）。例如"预测客户是否会流失"是一个二分类问题。

2. 数据收集
   确定数据来源：企业内部数据库、公开数据集、爬虫采集、问卷调查等。数据要真实、足量、覆盖面广。

3. 数据探索
   对数据进行EDA（探索性数据分析）：查看数据规模与字段含义、描述统计、缺失值与异常值检查、相关性分析、可视化观察规律。

4. 选择模型
   根据问题类型选择合适的算法：回归问题用线性回归/岭回归；分类问题用逻辑回归/决策树/随机森林；聚类问题用KMeans。

5. 参数估计
   用训练集对模型进行拟合（fit），学习模型参数；通过网格搜索等方式调整超参数，使模型达到最优表现。

6. 模型评估
   用测试集评估模型的泛化能力：分类看准确率/召回率/混淆矩阵，回归看MSE/R²；必要时进行交叉验证。

7. 模型诊断
   检查模型是否存在过拟合（训练集表现好、测试集差）、欠拟合（两者都差）；分析残差、特征质量与样本量，迭代改进。

8. 结果解释和应用
   把模型结果翻译成业务语言：提炼关键特征与规律，输出分析报告或Web应用等落地成果，并持续跟踪效果。