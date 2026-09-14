# Used to populate the SetStyle function because i'm lazy - Cray 14-09-2026

import tomli

with open("bin/GNU/config.toml", "rb") as f:
    cfg = tomli.load(f);

for x in cfg["STYLING"]:
    i = 0;
    for y in range(len(cfg["STYLING"][x])):
            i+=1
            if i % 4 == 0:
                print(f'ImColor(tbl["{x}"][0].value_or({cfg["STYLING"][x][0]}), tbl["{x}"][1].value_or({cfg["STYLING"][x][1]}), tbl["{x}"][2].value_or({cfg["STYLING"][x][2]}), tbl["{x}"][3].value_or({cfg["STYLING"][x][3]}))')
            else:
                 pass
