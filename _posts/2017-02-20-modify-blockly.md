---
layout: post
title: Modify the Source Code of Google's Open-source Framework --- Blockly
date:   2017-02-20 11:02:15 +0800
categories: Java Android Tech
comments: true
tags:
    - platform tool
---
<div class="message">
Blockly is an open-source framework under Apache 2.0 License for creating visual programming editors. It is a project of Google,which is able to run in web browser, Android or iOS operating system. 
Blockly uses blocks that link together to make writing code easier, and can generate JavaScript, Python, PHP, Lua or Dart code automatically. It can also be customised to generate code in any computer language.
</div>
  <!-- more -->

The use interface of Blockly consists of a toolbox, which holds all the availble blocks and a workspace, where you
place the blocks. There is a trashcan on the workspace which deletes any blocks dragged onto it. As is shown in the following picture:
![image](/assets/blog-img/2017_02_20_workspace.png "Blockly workspace")

Blockly comes with a basic set of blocks for common operations, but can be customized by adding more blocks. 
New blocks require a block definition and a generator. It is shown below:

![image](/assets/blog-img/2017_02_20_units.png "Blockly programming unit")

![image](/assets/blog-img/2017_02_20_example.png "Blockly programming example")

The definition describes the block's appearance and the generator describes the block's translation to executable code. 
There is an example program called Block Factory which makes writing the block definition easier by using Blockly blocks to construct a new block.

Now all its functions is adequate for most developers. However, it doesn't support dynamical loading blocks, e.g. in Android OS, the blocks' JSON-formated definition files are stored in the `assets` diirectory, obviously, all the files stored in this directory are regarded as system resources, they will be packaged into the .apk file, all of them are read only, i.e. they can only be read, but cannot be written back.
  
To manage to `dynamically load the blocks`, I tried two methods...
  
- Hook the OS functions. <br>
When the app process load the assets resources, we can `intercept relevant methods that load the blocks definition files`, read them out into other directory, and dynamically generate our own definition files then replace the paramaters with the new buffer that consists of the original definition files and the new generated file.
<br>It may sound unbelievable, however, there are many frameworks support dynamically hook Operating System's process that is running, e.g. [Xposed](https://github.com/googol-lab/Xposed) and [adbi](https://github.com/googol-lab/adbi). 
<br>However, Xposed may be unsuitable, since if you want to take use of its Java API you need to root your Android device, it may be unacceptable for most users. 
<br>Another instrumentation framework is adbi, which is short for Android Dynamic Binary Instrumentation Toolkit. With it you don't need to root your Android device, I haven't tried these framework yet, it may be useful, but Xposed does work.

- Modify the source code of Blockly to make it supporting dynamical loading blocks. <br>
For more details, see [here...](https://github.com/lijiansong/blockly-android)