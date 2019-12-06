var inp=POST.data;
var f=s=>s.replace(/([a-z0-9]|(?=[A-Z]))([A-Z])/g, '$1_$2').toLowerCase();
var ok='"Pistol,"AssaultRifle,"RocketLauncher'.split(",");
var out=inp;
ok.map((e,i)=>out=out.split(e).join("@"+i));
out=f(out);
ok.map((e,i)=>out=out.split("@"+i).join(e));
return out;