lines = IO.readlines(ARGV[0]);
lines.map!{|x| x.strip!}
lines.map!{|x|
	unless x.end_with?(";") then
		x+";"
	else
		x
	end
}
lines = lines.flat_map {|x| x.split(";").map{|s| s.strip}.reject{|item| item.start_with?("#") }.map{|s| s+";"}}
cnt = 0;
for s in lines do
	cnt = cnt + s.size
	if cnt >= 100 then
		puts ""
		cnt = 0;
	end
	print s
end

