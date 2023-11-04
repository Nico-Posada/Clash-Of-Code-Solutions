$winners = []

def get_string(idxs)
    c = 0
    idxs.map{|i| size=$words[i].length; ret=$og[c, size]; c+=size; ret}*' '
end

def solve(idxs, og_idx, c_arr_size)
    $size.times.each do |i|
        len = $words[i].length
        next if idxs.include?(i) || $og[og_idx, len] != $words[i]

        idxs << i
        if idxs.size == $size
            $winners << get_string(idxs)
            return true
        end

        r = solve(idxs, og_idx + len, c_arr_size + 1)
        if !r
            idxs = idxs[...c_arr_size]
        else
            return true
        end
    end

    return false
end

$og = gets.chomp
$words = gets.split
$size = $words.length

$words.size.times.select{$words[_1] == $og[...$words[_1].length]}.each do |idx|
    if solve([idx], $words[idx].length, 1) && $winners.size > 1
        if $winners[0] == $winners[1]
            $winners.pop
            next
        end
        puts "Unsolvable"
        exit
    end
end

puts $winners
