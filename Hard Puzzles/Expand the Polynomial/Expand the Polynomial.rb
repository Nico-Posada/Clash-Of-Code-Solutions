poly=gets.gsub(/(\(.*?\))\^(\d+)/){$1*$2.to_i}

groups = []
poly.scan(/\((.+?)\)/).map(&:first).each do |str|
    groups << str.scan(/\+?(-?\d*)(x?)(\^\d)?/).reject{_1+_2==''&&!_3}
end

while groups.size > 1
    g_a, g_b = groups[0], groups[1]
    result = {}

    g_a.each do |pre_a, x_a, exp_a|
        a_exp = exp_a ? exp_a[1..].to_i : x_a == ?x ? 1 : 0
        a_num = pre_a == '' ? 1 : pre_a == '-' ? -1 : pre_a.to_i

        g_b.each do |pre_b, x_b, exp_b|
            b_exp = exp_b ? exp_b[1..].to_i : x_b == ?x ? 1 : 0
            b_num = pre_b == '' ? 1 : pre_b == '-' ? -1 : pre_b.to_i

            t_exp = a_exp + b_exp
            result[t_exp]=[] if !result[t_exp]
            result[t_exp] << a_num * b_num
        end
    end

    result = result.transform_values(&:sum).map{
        [_2 == 1 ? '' : _2.to_s, _1 == 0 ? '' : ?x, _1 == 0 || _1 == 1 ? nil : ?^ + _1.to_s]
    }

    groups[..1] = [result]
end

final = groups.first.select{_1[0] != '0'}.map{|a|
    arr = a.select{_1}
    num = arr[0].to_i
    num.abs != 1 || arr[1] == '' ? arr.join : num == -1 ? ?- + arr[1..].join : arr[1..].join
}*?+

puts final.gsub('+-','-')
