
Slight documentation:


CLFE - c library framework engine
CLU - c library utilities
CLM - c library math


macros:

CLFE_XX_H - header guards for components in clfe
CLU_XX_H - header guards for components in clu
CLM_XX_H - header guards for components in clm



Attachment priorities: (the lower the number the higher the priority, the earlier it is called in the chain)
System - 10
Window - 50
Windows Window - 70
Mac Window - 75
Linux Window - 80
System Input - 100



Naming conventions to follow:
Variables inside clfe namespace or attachments: pascalcase (e.g. MyComponent, MyFunction, MyVariable)
Variables that are "static" and of constant nature: pascalcase (overlaps with previous rule)
All other cases: camelcase (e.g. myComponent, myFunction, myVariable)



Components to include:

Window - window system
InputSystem - input system for all windows
CLFE - init, step, and terminate for all engine components

CLM - include any math components needed, most will be automatically included due to dependency from other components
CLU - include any utility components needed, many will be automatically included due to dependency from other components



System conventions:
- Only attachment components should and can be fully initialized statically. All other static components must be initialized again in the init function.
- Terminate must be able to return the engine to a state similar to before initialization, meaning that all resources must be freed. Then, init must be able to be called again without issue and leaked memory.
- All components must have a deletion that fully cleans its own resources and all of its dependencies (except InstanceList).

IMPORTANT: based on above conventions, NEVER create engine objects before initializing the system!!! There will be many problems!!! Of course, the math and utility components do not require the initialization to be used.
