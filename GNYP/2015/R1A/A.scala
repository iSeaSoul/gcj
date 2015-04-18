import scala.io.Source

def solve(caseNum:Int, line:String):Unit = {
    var numbers = line.split(' ').map(ch => ch.toInt)
    val n = numbers.length
    var res1 = 0
    for (idx <- 0 until n - 1) {
        if (numbers(idx + 1) < numbers(idx)) {
            res1 += numbers(idx) - numbers(idx + 1)
        }
    }
    var res2 = 0
    var maxdiff = 0
    for (idx <- 0 until n - 1) {
        maxdiff = math.max(maxdiff, numbers(idx) - numbers(idx + 1))
    }
    for (idx <- 0 until n - 1) {
        res2 += math.min(maxdiff, numbers(idx))
    }

    println("Case #" + caseNum + ": " + res1 + ' ' + res2)
}

var caseNum = 0
Source.fromFile("A.in").getLines.foreach { line =>
    if (caseNum != 0 && caseNum % 2 == 0) {
        solve(caseNum / 2, line)
    }
    caseNum += 1
}
