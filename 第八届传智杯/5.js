const rl = require("readline").createInterface({ input: process.stdin });
var iter = rl[Symbol.asyncIterator]();
const readline = async () => (await iter.next()).value;

void (async function () {
  // 数量
  const n = parseInt(await readline());

  // 药物信息
  const yao = [];
  for (let i = 0; i < n; i++) {
    const line = await readline();
    const tokens = line.split(" ");
    const a = parseInt(tokens[0]); // 疼痛值
    const b = parseInt(tokens[1]); // 疗效值
    yao.push({ a, b });
  }

  // 先对每个疼痛值，找到其最大疗效值
  const painMap = new Map();
  for (let i = 0; i < n; i++) {
    const a = yao[i].a;
    const b = yao[i].b;
    if (!painMap.has(a) || painMap.get(a) < b) {
      painMap.set(a, b);
    }
  }

  // 按疼痛值排序
  const pV = Array.from(painMap.keys()).sort((a, b) => a - b);

  // 构建前缀最大值数组
  const pM = [];
  let mE = -1;
  for (let i = 0; i < pV.length; i++) {
    mE = Math.max(mE, painMap.get(pV[i]));
    pM.push(mE);
  }

  const q = parseInt(await readline());

  for (let i = 0; i < q; i++) {
    const x = parseInt(await readline());

    // 二分查找 找最大疼痛值
    let left = 0;
    let right = pV.length - 1;
    let result = -1;

    while (left <= right) {
      const mid = Math.floor((left + right) / 2);
      if (pV[mid] <= x) {
        result = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    if (result === -1) {
      console.log(-1);
    } else {
      console.log(pM[result]);
    }
  }
})();
