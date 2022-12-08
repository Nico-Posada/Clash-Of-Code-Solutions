public def to_bin
  self.map{_1 ? 1 : 0}.join.sub(/0+(?!.*1)/,'').chars # strips extra 0's at the end
end

def makePlus(grid, t, x, y, size)
  len = (size-t+2)/2
  x_idx = size * x
  y_idx = size * y

  # write values that do not need checks
  grid[y_idx+size-1][x_idx+len-1...x_idx+len-1+t] = [true]*t
  grid[y_idx+len-1][x_idx...x_idx+len] = [true]*len
  grid[y_idx+len-1][x_idx+len+t-2...x_idx+len*2+t-2] = [true]*len
  grid[y_idx+len+t-2][x_idx...x_idx+5] = [true]*len
  grid[y_idx+len+t-2][x_idx+len+t-2...x_idx+len*2+t-2] = [true]*len

  (len-2).times do |i|
    grid[y_idx+1+i][x_idx+len-1] = true
    grid[y_idx+1+i][x_idx+len+t-2] = true
  end

  (len-2).times do |i|
    grid[y_idx+len-1+t+i][x_idx+len-1] = true
    grid[y_idx+len-1+t+i][x_idx+len+t-2] = true
  end

  (t-2).times do |i|
    grid[y_idx+len+i][x_idx+size-1] = true
  end

  # write values that do need checks
  if y > 0 && grid[y_idx-1][x_idx+len-1] == true
    grid[y_idx-1][x_idx+len...x_idx+len+t-2] = [false]*(t-2)
    grid[y_idx][x_idx+len-1] = true
    grid[y_idx][x_idx+len-2+t] = true
  else
    grid[y_idx][x_idx+len-1...x_idx+len-1+t] = [true]*t
  end

  if x > 0 && grid[y_idx+len][x_idx-1] == true
    (t-2).times do |i|
        grid[y_idx+len+i][x_idx-1] = false
    end
  else
    (t-2).times do |i|
        grid[y_idx+len+i][x_idx] = true
    end
  end

  return grid
end

size, thickness, line_count, *lines = $<.map &:chomp
thickness = thickness.to_i
size = size.to_i
t_width = size*lines.map(&:length).max
t_height = size*line_count.to_i

grid = Array.new(t_height){Array.new(t_width){false}}
for y in 0...lines.size
  lines[y].chars.each_with_index do |c, x|
    grid = makePlus(grid, thickness, x, y, size) if c == ?+
  end
end

grid.each do |line|
  line.to_bin.each{putc _1 == ?1 ? ?+ : ' '}
  puts
end
