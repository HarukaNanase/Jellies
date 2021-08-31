The objective is to combine jellies and save as many as possible before they reach the end of the platform.
The game is set to work with combinations of 2 or more adjacent jellies and a new column spawns each 3 seconds.
The score is updated upon each valid move and a record is kept during gameplay and is shown at the end.
Play is done with the left mouse button, by clicking on the desired jelly.
Pressing P while the game is ongoing will pause the game.


This engine behind Jellies, named as BlocksEngine is a 2D game engine running over SDL and SDL libraries.
The following list depicts the libraries and versions used:
- SDL2 - 2.0.10
- SDL2_Image - 2.0.5
- SDL2_mixer - 2.0.4
- SDL2_ttf - 2.0.15

A non-sdl library can also be used for the sound system and is included as well as a system ready to work in engine.
-irrKlang - 1.6.0


The engine itself is an hybrid ECS (entity component system) but some people might call it just an EC system. This design was taken in mind due to the
extensability and ease of adding new features by the addition of new components/systems while keeping the ease of use of polymorph game objects, which enable
something like a scripting language to be used for the creation of the objects for a game.

The following classes make the game:

HUD: A hud class that contains the play button, quit button and score windows.
Jelly: represents a single jelly
Grid: The grid where new jelly columns are placed. A 2d dynamic matrix that can have columns removed in any position as well as any element from columns.
EndPoint: the end point for the game. Detects collision with the grid and calls the end menu on the HUD class.
JelliesGame : The game launching mechanism, creates a copy of each required object and adds a copy to the world.



The entity, GameObject, represents an object inside the game world. Each gameobject can possess Components that alter the behavior and the systems that can track it.
GameObjects are incredibly abstract and as such can become anything from a background, to an object in the game, to an interactable and even a GUI button.
GameObjects can be derived to implement specific logic and can be added to the world.
GameObjects possess a component mask, a bitset, that tells a system if there is interest to be processed by it.

Components are mostly data and the following components are included:
CollisionComponent - enables collisions for the object and specifies the callbacks to be called (kept as std::functions)
InputComponent - enables mouse/keyboard input for the component
MovementComponent - enables the ability to lerp between 2 positions over time
SoundComponent - enables the ability to play sounds
TextComponent - enables text rendering
TransformComponent - enables positioning into the world.

As specified, each component is basically data to be interpreted and executed by the systems. The following systems are included:

AudioSystem - processes the soundcomponents and plays a sound if any was requested. Uses irrKlang as the sound engine.
CollisionSystem - detects collisions and executes callbacks for each object in a collision, passing the other as a parameter.
InputSystem - tracks events and executes callbacks on objects that requested a specific event.
MixerAudioSystem - processes the soundcomponents and plays a sound if any was requested. Uses SDL_Mixer as the sound engine.  
MovementSystem - executes the lerp over time of an object.
RenderSystem - uses SDL rendering API to draw textures/sprites to the screen

The world is the central entity of the engine and keeps track of both existing systems and gameobjects with strong ownership over both. Creation and deletion of
game objects is done solely by the world. When a system wants to update, it requests a view of the gameobjects whose mask has a bit equal to the required components
for that system. This view is guaranteed to be valid until the end of the current frame.


Resources:
As with any game engine, we require to load resources from the hard drive into memory to use them. Due to SDL way of loading most resources, wrappers were written
around the SDL types to make memory management easier.

The following wrappers and their SDL type:

Texture - holds a SDL_Texture* pointer. Calls SDL_DestroyTexture on object destruction.
Audio - can hold both a Mix_Chunk* or a Mix_Music* pointer, identified by a type variable. Calls SDL_FreeMusic/SDL_FreeChunk on object destruction.
Font - holds a TTF_Font* pointer. Calls TTF_CloseFont on object destruction.

Each resource type is loaded and held by a ResourceManager. We can derive from the template ResourceManager<MT, T> to
create new managers that are not included. Each manager keeps a map between a string and an unique pointer,  in order to ensure clean up of resources by calling
the class destructor upon removal of resource.
Managers Included:
TextureManager : handles loading, creation and deletion of Textures.
AudioManager : handles loading, creation and deletion of Sounds to use with irrKlang sound engine.
MixerAudioManager: handles loading, creation and d eletion of Audio to use with SDL_Mixer sound engine.


Other utility classes are included:
Engine class - does the init and quit of SDL and other more general libraries
Vector2 - a 2d vector (x,y)
Color - a 4-component color, RGBA
Camera2D - a 2d camera that transforms screen coordinates to world coordinates and accounts for the automatic scaling that SDL does with SDL_RenderSetLogicalSize.





