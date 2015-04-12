import scala.io.Source

def solve(line:String):Boolean = {
    var n = line.split(' ').map(ch => ch.toInt)
    var X = n(0)
    var R = n.slice(1, 3).max
    var C = n.slice(1, 3).min
    if (X == 1) {
        return true
    }
    if (X >= 7) {
        return false
    }
    if (R * C % X != 0) {
        return false
    }
    if (X <= 4) {
        return C >= X - 1
    }
    if (X == 5) {
        return C >= 3 && !(R == 5 && C == 3)
    }
    return C >= X - 2
}

var caseNum = 0
Source.fromFile("D.in").getLines.foreach { line =>
    if (caseNum != 0) {
        println("Case #" + caseNum + ": " + {if (solve(line)) "GABRIEL" else "RICHARD"})
    }
    caseNum += 1
}
