# GridRunner Copycat (WIP)
This project is a copycat project of the Sega Saturn/PS1 game [GridRunner](https://en.wikipedia.org/wiki/Grid_Runner) from 1996 implemented in Unreal Engine 5.1.
I played it a lot growing up and I thought it would be a good exercise to implement the game in Unreal Engine as a learning experience.

### Development Environment:
- Unreal Engine 5.1.1 (From Epic Games Launcher, not full source code)
- Visual Studio 2022 Professional v17.6.6
- Visual Assist 2023.3

### Coding Standards and Style Guide:
This project adheres to the [Epic C++ Coding Standard](https://docs.unrealengine.com/5.1/en-US/epic-cplusplus-coding-standard-for-unreal-engine/).
One addition I make to this standard is that I like to prefix all member variables and methods with `this`. When working with a codebase the size of Unreal Engine, this makes it easier to scan code and tell at a glance when something is inherited, a member, or local, etc.

This project also follows Allar's [UE5 Style Guide](https://github.com/Allar/ue5-style-guide) for general folder structure and asset naming conventions except where it would directly contradict the [Epic C++ Coding Standard](https://docs.unrealengine.com/5.1/en-US/epic-cplusplus-coding-standard-for-unreal-engine/).
