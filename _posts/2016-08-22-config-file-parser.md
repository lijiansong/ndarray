---
layout: post
title: Config File Parser
categories: Yacc Cpp
comments: true
tags:
    - IDL
    - platform tool
---

<div class="message">
  This archive is about how to use Flex and Bison (Yacc) to parse config files that is self-defined. 
</div>The contens is shown below:<br>
<!-- more -->

* [Description File Design](#description-file-design)
  * [Key-Values](#key-values)
  * [Inheritance Mechanism](#inheritance-mechanism)
  * [Induction Mechanism](#induction-mechanism)
  * [Comments](#comments)
* [Syntax Design](#syntax-design)
* [Usage](#usage)

## Description File Design

### Key-Values

> Format of the config file is similar to JSON, which is composed of pairs of key-values. The config file is also composed of some tuples, which contain some pairs of key-values. e.g.

{% highlight js %}
section {
 key1 = "string";
 key2 = 12.34;
}
{% endhighlight %}

> Therefore,

{% highlight js %}
section.key1= "string"
section.key2=12.34
{% endhighlight %}

### Inheritance Mechanism

> Besides the features above, the config file also supports inheritance mechanism. The symbol of inheritance is shown by ":", e.g.<br>

{% highlight js %}
derived_section : section {
  key1 = "override string";
  key3 = 10;
}
{% endhighlight %}

> Therefore,

{% highlight js %}
derived_section.key1="override string"
derived_section.key2=12.34
derived_section.key3=10
{% endhighlight %}

> The types of the config file include int, float, string.<br>

### Induction Mechanism

> The config file also introduces induction mechanism, which is expressed by "include", e.g.<br>
> The contents of a.config:

{% highlight js %}
section_a {
 key1 = "string";
 key2 = 12.34;
}
{% endhighlight %}

> The contents of b.config:

{% highlight js %}
#include "path/a.config"
section_b {
 key1 = "str1";
 key2 = 12.34;
x{
 key1=2;
 key2=8;
}
y : section_b.x{
 key1=20;
 key3=33;
}
}
z:section_a{
key1="str";
key2=25;
}
{% endhighlight %}

### Comments

> The config file also supports comments, formularized by /*comments*/ or //, e.g.<br>

{% highlight js %}
//comment
section {
 key1 = /* comment*/ "string";
 key2 = 12.34;
}
{% endhighlight %}

## Syntax Design

> To parse the config file, flex & bison is of much efficiency. Before using the mature tools, we have to define the grammar in advance, which is formularized by Backus-Naur Form. The config files' Backus-Naur Form is shown below:<br>

```
tuples::= tuple tuples | \epsilon
tuples::= ID LB entries RB | ID COLON LB entries RB
entries::= kv entries | tuple entries | \epsilon
kv::= ID EQ value END
value::= FLOAT | INT | ctring | NULLV
cstring::= STRING cstring

INT->[0-9]+
FLOAT->[+-]?[0-9]+(\.[0-9]*)?
STRING->\"(\\.|[^\\"])*\"
ID->[a-z_][a-z0-9_\.]*
LB->{
RB->}
COLON->:
EQ->=
END->;
NULLV->NULL
```

## Usage

> To Compile the source code, you need to install git & make. You can use the following command line to complie them:

{% highlight js %}
$ git clone https://github.com/lijiansong/ConfigFileParser
$ cd ConfigFileParser
$ make
{% endhighlight %}

> After the above cmds, you would get an executable file, named *config_parser*, and a static library suffixed by *.a*, named *lib_cfg_parser.a*. You can execute it like this( before use it you need to write a config file that is formulized by the grammar defined above ):

{% highlight js %}
$ ./config_parser test.config
{% endhighlight %}

> You can also call the static library *lib_cfg_parser.a* in your own program.<br>[To learn more...](https://github.com/lijiansong/ConfigFileParser)


-----

Want to see something else added? <a href="https://github.com/lijiansong/ConfigFileParser/issues">Open an issue.</a>
