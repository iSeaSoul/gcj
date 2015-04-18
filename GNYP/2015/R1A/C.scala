import scala.io.Source

class Point(xx:Double, yy:Double) {
    var x = xx
    var y = yy

    def print():Unit = {
        println(x, y)
    }
    def subtract(p:Point):Point = {
        new Point(x - p.x, y - p.y)
    }
    def atan2():Double = {
        math.atan2(y, x)
    }
}

def solve(caseNum:Int, points:Vector[Point]):Unit = {
    val n = points.length
    println("Case #" + caseNum + ":")
    if (n <= 3) {
        for (t <- 0 until n) println(0)
        return
    }
    for (i <- 0 until n) {
        var atanv = Vector[Double]()
        for (j <- 0 until n) {
            if (i != j) {
                val atanx = points(j).subtract(points(i)).atan2
                atanv :+= atanx
                atanv :+= atanx + 2 * math.Pi
            }
        }
        atanv = atanv.sorted
        var idx = 0; var ret = n
        for (j <- 0 until n - 1) {
            while (idx != 2 * n - 2 && atanv(j) + math.Pi - 1e-8 >= atanv(idx)) {
                idx += 1
            }
            ret = math.min(idx - j - 1, ret)
        }
        println(ret)
    }
}

var lineNum = 0
var caseNum = 1
var caseLineNum = 0
var points = Vector[Point]()

Source.fromFile("C.in").getLines.foreach { line =>
    if (lineNum != 0) {
        if (caseLineNum == 0) {
            caseLineNum = line.toInt
            points = Vector[Point]()
        } else {
            val arr = line.split(' ').map(ch => ch.toDouble)
            points :+= new Point(arr(0), arr(1))
            caseLineNum -= 1
            if (caseLineNum == 0) {
                solve(caseNum, points)
                caseNum += 1
            }
        }
    }
    lineNum += 1
}
