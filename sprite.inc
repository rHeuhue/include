#if defined _sprite
  #endinput
#endif
#define _sprite

native DisplaySprite( id , const SpriteName[ ] , Float:SpriteSize = 0.03 , StopFrame = 0 , Float:FrameRate = 0.0 );

native RemoveSprite( id );