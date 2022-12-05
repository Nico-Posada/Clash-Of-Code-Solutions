def distance(x1, y1, x2, y2)
    return Math.sqrt( (y2-y1)**2 + (x2-x1)**2 )
end

instructions = gets.chomp.split.map{ |ins| ins.scan(/(PLANT|PLANTMOW)*(.)(.)(\d+)/)[0] }
grid = Array.new(25) { Array.new(19){?x} }

instructions.each do |extra, x, y, d|
    col = x.ord-97
    row = y.ord-97
    rad = d.to_f/2.0

    for y in 0...25
        for x in 0...19
            dis = distance(x, y, col, row)
            if rad >= dis
                if extra.nil?
                    grid[y][x] = ' '
                elsif extra == "PLANT"
                    grid[y][x] = 'x'
                elsif extra == "PLANTMOW"
                    grid[y][x] = grid[y][x] == ?x ? ' ' : ?x
                end
            end
        end
    end
end
grid.map! {_1.join.gsub(?x,'{}').gsub(' ', '  ')}
puts grid
