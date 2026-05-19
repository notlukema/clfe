Rewriting the README here (from the 4th)



Details:


Certain files are split into implementation and user versions, either for user-specific features or to manage dependencies. The naming convention for these files is as follows:

*Implementation Files*
Files ending in '_i' are engine-level implementations. They are either designed to stay internal or contain code strictly required by the engine to run (abstract away supplementary functionality).
- Include guards for these files also contain the '_i' suffix
- These files are not intended to be used directly unless the user knows what they are doing
- Files designed to completely stay internal will not have a "user file" version, but they w

*User Files*
Files not ending '_i' are all good for user inclusions. They may contain supplementary code that provides features valuable to users.
- Include guards for these files do not contain the '_i' suffix
- Not every one of these files will contain additional code


Header guard naming conventions:

Header guards are built in close relation to their file paths and component relationships:
- [BRANCH]_[BASE COMPONENT]_[COMPONENT RELATIONSHIPS]_H
- [BRANCH]_[BASE COMPONENT]_[COMPONENT RELATIONSHIPS]_I_H for implementation files

Examples:
- CLFE_WINDOW_H and CLFE_WINDOW_I_H
- CLFE_PIPELINE_VULKAN1_4_H and CLFE_PIPELINE_VULKAN1_4_I_H
- CLM_VECTOR_2_H


Header guard specifics:

Implementation files add an '_i' suffix to their header guards.
- Ex. CLFE_WINDOW_I_H

User files do not add the '_i' suffix to their header guards.
- Ex. CLFE_WINDOW_H
- The existence of these headers must mean that the corresponding implementation version (if it exists) is also present
