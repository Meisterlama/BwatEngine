LUA
===

Getting Started
###############

To start developing gameplay with the Lua API, you should download VS Code ans install the `Lua plugin`_.

.. _Lua plugin: https://marketplace.visualstudio.com/items?itemName=keyring.Lua

.. note::
    The plugins on CLion and VS are a bit of heavy weight and overkill for what's in place on BwatEngine.

Currently there is no page where **all** the exposed functions are explained, so you must go through the sources.

The files you're interested in are located at Engine/src/Scripting. The functions are registered in the functions
`open_<module>()` at the end of the related .cpp file. They are written as a macro `REGISTER_FUNC()` or as
`module.set_function()`.

common.cpp
##########

Contains various functions that currently doesn't fit in a specific module (Such as creating an entity and logging)

components.cpp
##############

Contains all the functions related to the ECS's components. Each function takes the entity's ID as first argument.
The functions name are the same as their C++ equivalent ones (subject to change if some overlapping happen).
Those functions don't check if the entity have the component before getting it (i.e. it will crash the script if the
entity doesn't have the required component)

input.cpp
#########

Contains all the functions related to inputs. The functions are the same as in C++ except that the enum is changed for a
string.

.. code-block:: cpp

    InputHandler::GetKeyboard(KEY_W);

becomes

.. code-block:: lua

    input.GetKeyboard("w")

math.cpp
########

This module is quite edgy. Lua have a standard module for math functions, but BwatEngine overrides it to expose its
math related structs and functions. The different plugins will hint you to autocomplete with those functions, **but they
are not exposed**. The defined functions are the same as the BwatEngine math library, with the same names.