def search(word, idx, x, y, dir)
    directions = dir ? [dir] : [[1,1],[1,0],[0,1],[0,-1],[-1,0],[-1,-1],[1,-1],[-1,1]]

    for dx,dy in directions
        nx,ny=dx+x,dy+y
        next if nx<0||nx>=$r||ny<0||ny>=$r||$g[ny][nx]!=word[idx]

        if idx==word.length-1
            return [nx,ny,*dir]
        else
            result = search(word, idx+1, nx, ny, [dx,dy])
            next if !result

            return result
        end
    end

    return nil
end

$r=gets.to_i
$g=$r.times.map{gets.chomp}
l=gets.chomp

warn "#{$r} #{$g.size} #{l.split.size}"
result=Array.new($r){[' ']*$r}
l.split.map(&:upcase).each do |word|
    for y in $r.times
        for x in $r.times
            next if $g[y][x] != word[0]

            final_coords = search(word, 1, x, y, nil)
            next if !final_coords

            rx,ry,dx,dy=final_coords
            dx*=-1
            dy*=-1

            for i in word.length.times
                result[ry][rx] = word[~i]
                rx+=dx
                ry+=dy
            end
        end
    end
end

puts result.map(&:join)
