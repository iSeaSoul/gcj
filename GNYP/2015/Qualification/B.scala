import scala.io.Source

def solve(caseNum:Int, line:String):Unit = {
    var numbers = line.split(' ').map(ch => ch.toInt)
    var res = numbers.max
    for (limit <- 1 until numbers.max) {
        var sum = 0
        numbers.foreach { num => sum += (num - 1) / limit }
        if (sum + limit < res) {
            res = sum + limit
        }
    }
    println("Case #" + caseNum + ": " + res)
}

var caseNum = 0
Source.fromFile("B.in").getLines.foreach { line =>
    if (caseNum != 0 && caseNum % 2 == 0) {
        solve(caseNum / 2, line)
    }
    caseNum += 1
}
