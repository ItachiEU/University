process.stdin.on("readable", () => {
   let name = process.stdin.read();
   console.log(`Hello ${name}`)
})