# crappy but whatever
def play(grid, num)
    case num.to_i
    when 1
        grid[0][0] ^= 1
        grid[0][1] ^= 1
        grid[1][0] ^= 1
        grid[1][1] ^= 1
    when 2
        grid[0][0] ^= 1
        grid[0][1] ^= 1
        grid[0][2] ^= 1
    when 3
        grid[0][2] ^= 1
        grid[0][1] ^= 1
        grid[1][2] ^= 1
        grid[1][1] ^= 1
    when 4
        grid[0][0] ^= 1
        grid[1][0] ^= 1
        grid[2][0] ^= 1
    when 5
        grid[0][1] ^= 1
        grid[1][0] ^= 1
        grid[1][1] ^= 1
        grid[1][2] ^= 1
        grid[2][1] ^= 1
    when 6
        grid[0][2] ^= 1
        grid[1][2] ^= 1
        grid[2][2] ^= 1
    when 7
        grid[2][0] ^= 1
        grid[2][1] ^= 1
        grid[1][0] ^= 1
        grid[1][1] ^= 1
    when 8
        grid[2][0] ^= 1
        grid[2][1] ^= 1
        grid[2][2] ^= 1
    when 9
        grid[2][2] ^= 1
        grid[2][1] ^= 1
        grid[1][2] ^= 1
        grid[1][1] ^= 1
    end

    return grid
end

*grid, presses = $<.map &:chomp
grid.map! do |line|
    line.split.map{_1 == ?~ ? 0 : 1}
end

presses.chars do |num|
    grid = play(grid, num)
end

win = [[1,1,1],[1,0,1],[1,1,1]]
for i in 1..9
    # have to clone grid to avoid the original grid getting modified
    clone = Marshal.load(Marshal.dump(grid))

    if win == play(clone, i)
        puts i
        exit
    end
end
