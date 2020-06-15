# 2020-pd2-DoodleJump

## How to play

Press `A` `D` or `Left` `Right` to control character.  
And Press "pause button" or press `P` to pause or resume.  

### Items

Hopter: Can fly in few seconds.  
Shield: Can protect from being hurt by bomb.  

### Hazards

Bomb: Can use bullet to remove or avoid it by shield.  
Hole: No way to avoid it.  

### Special platform

There is a kind of platform that is fragile, you can only step once.  

## Requirements

None.  

## Polymorphism

Use `platform_base` as base class.  
`normal_platform` and `fragile_platform` inherit from it.  
The base class provide a function `be_jumped()`.  
And each platform implement the function seperately.  
e.g. `fragile_platform` should be deleted after stepped.  

## Bonus

My "pause button" will change icon when it paused.
