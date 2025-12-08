const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

let t = null;
let done = 0;
let out = [];

rl.on("line", (line) => {
  const s = line.trim();
  if (s === "") return;

  if (t === null) {
    t = parseInt(s, 10) || 0;
    if (t === 0) rl.close();
    return;
  }

  const arr = s.split(/\s+/).map(Number);
  const a = arr[0],
    b = arr[1],
    c = arr[2],
    d = arr[3];

  if (a === b && b === c && c === d) {
    out.push("YES");
  } else {
    out.push("NO");
  }

  done++;
  if (done >= t) rl.close();
});

rl.on("close", () => {
  if (out.length) {
    console.log(out.join("\n"));
  }
});
