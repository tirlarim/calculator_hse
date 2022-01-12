`use strict`;

const calculator = (mathProblemArr) => {
  const operation = {
    multiply: `*`,
    divide: `/`,
    add: `+`,
    subtract: `-`,
    exponent: `^`,
  }
  const brackets = {
    open: `(`,
    close: `)`,
  }
  while (mathProblemArr.includes(brackets.open)) {
    let openCount = 0;
    let closeIndex = -1;
    let openIndex = mathProblemArr.indexOf(brackets.open);
    for (let i = 0; i < mathProblemArr.length; i++) {
      if (mathProblemArr[i] === brackets.open) {
        openCount++;
        continue;
      }
      if (mathProblemArr[i] === brackets.close) {
        openCount--;
        if (openCount === 0) {
          closeIndex = i;
          break;
        }
      }
    }
    mathProblemArr = [...mathProblemArr.slice(0, openIndex), ...calculator(mathProblemArr.slice(openIndex+1, closeIndex)), ...mathProblemArr.slice(closeIndex+1)];
  }
  if (!mathProblemArr.includes(brackets.open)) {
    while (mathProblemArr.length > 1) {
      while (mathProblemArr.includes(operation.exponent)) {
        let exponentSymbolIndex = mathProblemArr.indexOf(operation.exponent);
        mathProblemArr = [...mathProblemArr.slice(0, exponentSymbolIndex-1), Math.pow(mathProblemArr[exponentSymbolIndex-1], mathProblemArr[exponentSymbolIndex+1]), ...mathProblemArr.slice(exponentSymbolIndex+2)];
      }
      while (mathProblemArr.includes(operation.multiply) || mathProblemArr.includes(operation.divide)) {
        let multiplySymbolIndex = mathProblemArr.indexOf(operation.multiply);
        let divideSymbolIndex = mathProblemArr.indexOf(operation.divide);
        if ((divideSymbolIndex === -1 || multiplySymbolIndex <= divideSymbolIndex) && multiplySymbolIndex !== -1) {
          mathProblemArr = [...mathProblemArr.slice(0, multiplySymbolIndex-1), mathProblemArr[multiplySymbolIndex-1] * mathProblemArr[multiplySymbolIndex+1], ...mathProblemArr.slice(multiplySymbolIndex+2)];
        } else {
          mathProblemArr = [...mathProblemArr.slice(0, divideSymbolIndex-1), mathProblemArr[divideSymbolIndex-1] / mathProblemArr[divideSymbolIndex+1], ...mathProblemArr.slice(divideSymbolIndex+2)];
        }
      }
      while (mathProblemArr.includes(operation.add) || mathProblemArr.includes(operation.subtract)) {
        let addSymbolIndex = mathProblemArr.indexOf(operation.add);
        let subtractSymbolIndex = mathProblemArr.indexOf(operation.subtract);
        if ((subtractSymbolIndex === -1 || addSymbolIndex <= subtractSymbolIndex) && addSymbolIndex !== -1) {
          mathProblemArr = [...mathProblemArr.slice(0, addSymbolIndex-1), mathProblemArr[addSymbolIndex-1] + mathProblemArr[addSymbolIndex+1], ...mathProblemArr.slice(addSymbolIndex+2)];
        } else {
          mathProblemArr = [...mathProblemArr.slice(0, subtractSymbolIndex-1), mathProblemArr[subtractSymbolIndex-1] - mathProblemArr[subtractSymbolIndex+1], ...mathProblemArr.slice(subtractSymbolIndex+2)];
        }
      }
    }
    return mathProblemArr;
  }
}

const task = () => {
  let values = {};
  let file = require(`fs`).readFileSync(`./tests/input.txt`,`utf8`).toString().split(`\n`);
  let problem = file.shift().replace(/ /g, ``).split(/([$-/:-?{-~!"^_`\[\]])/g).filter((item) => item !== ``).map((item) => isNaN(Number(item)) ? item : Number(item));
  file.forEach((item) => values[item.split(` `)[0]] = Number(item.split(` `)[2]));
  problem.forEach((item, index) => Object.keys(values).includes(item) ? problem[index] = values[item] : item);
  console.log(...problem);
  console.log(values);
  console.log(calculator(problem));
}

task();
