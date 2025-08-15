---@class BaseTank
---@field health integer
---@field position_x number
---@field position_y number

---@class WorldAPI
---@field load_map fun(name:string)
---@field start_map fun()
---@field spawn_light_tank fun(x:number, y:number):integer
---@field get_tank fun(id:integer):BaseTank
---@field create_player fun(tank_id:integer)
---@field set_camera_follow fun(tank_id:integer)
---@field command_move_to fun(tank_id:integer, x:number, y:number)

---@type WorldAPI
World = World
