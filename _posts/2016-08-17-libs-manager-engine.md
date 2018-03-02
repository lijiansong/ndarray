---
layout: post
title: Libs-Manager-Engine
categories: Android Java
comments: true
tags:
    - IDL
    - platform tool
---


<div class="message">
  I have been coding an platform recently, which can manage library binaries on end users devices, such as android, iOS and so on.

</div>

The platform is a Service Store, which just like the app store in android, where delelopers develop their own apps and deploy them onto the app store, and users can download the app that they like and install it on his or her devices. Therefore, android's app store can be treated as an ecological system.
<!-- more -->
However, our Service Store is also an ecological system, where the Service Manufacture or Lib Developers can develop their own Cloud Services or Native Services, and users can connect to the service they like on their end devices, e.g. *Voice Recognition Service*, *Face Detection Service*, etc. The technical architecture of the platform is shown below.


**Technical Architecture**

![image](/assets/blog-img/2016_08_17_arch.png "Technical Architecture")

On Andrioid platform, it provides [*AIDL*](https://developer.android.com/guide/components/aidl.html) for developers. AIDL (Android Interface Definition Language) is similar to other IDLs you might have worked with. It allows you to define the programming interface that both the client and service agree upon in order to communicate with each other using interprocess communication (IPC). On Android, one process cannot normally access the memory of another process. So to talk, they need to decompose their objects into primitives that the operating system can understand, and marshall the objects across that boundary for you. The code to do that marshalling is tedious to write, so Android handles it for you with AIDL. With AIDL, developers don't need to know the underlying Binder mechanisms.

Introduction
---
Refer to the OpenCV Manager Mauual.
Just like the OpenCV Manager, the Engine Manager is also an Android service targeted to manage OpenCV library binaries on end users devices. It allows sharing the dynamic libraries between applications on the same device, such as Face Detection lib, Voice Recognition lib. The Engine Manager provides the following benefits:
- Less memory usage. All apps use the same binaries from service and do not have to keep the native libs inside themselves;
- Hardware specific optimizations for all supported platforms, such as the different CPU-Arch of Android platform;
- Once the Engine is released, all the Service Libraries will be trusted library source. All packages with OpenCV should be published on Google Play market or Apple's App Store;
- Regular updates and bug fixes;

> [Learn more details...](https://github.com/lijiansong/Libs-Manager-Engine/blob/master/engine/README.md)

-----

Want to see something else added? <a href="https://github.com/lijiansong/Libs-Manager-Engine/issues">Open an issue.</a>
