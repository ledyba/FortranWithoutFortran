package generator

import java.io._
import scala.util.Random

object Main {
	def using[A, B <: Closeable](s: B)(f: B=>A):A = {
		try {
			f(s)
		} finally {
			s.close()
		}
	}
	def load(f_ : String, start : Int, end : Int) : Array[Int] = {
		def readInt(fis : InputStream):Int = {
			var r:Int = 0;
			var i:Int = 0;
			r = fis.read();
			if( r < 0 ) {
				throw new Exception();
			}
			i = fis.read();
			if( i >= 0 ){
				r = r | (i << 8);
			}
			i = fis.read();
			if( i >= 0 ){
				r = r | (i << 16);
			}
			i = fis.read();
			if( i >= 0 ){
				r = r | (i << 24);
			}
			r
		};
		var lst = Array[Int]();
		using(new FileInputStream(f_)) { f =>
			val buf = new Array[Byte](end-start);
			f.skip(start);
			f.read(buf);
			val bf = new ByteArrayInputStream(buf);
			try {
				while(true) {
					lst = lst :+ readInt(bf);
				}
			} catch {
				case _ : Throwable => return lst;
			}
			lst;
		}
	}
	def gen(outf : String, codes : Array[Int], ep : Int) = {
		val r = new Random();
		def gensym() = "gensym"+r.nextDouble() * 10000000000000L;
		using(new PrintStream(new File(outf))) { f =>
			f.println("x(1)%%x => d(%d)".format(ep))
			for((i,code) <- Stream.from(1).zip(codes)) {
				f.println("d(%d)=%d;".format(i,code));
			}
		}
	}
	def main(args:Array[String]):Unit = {
		val file = args(0);
		var start = Integer.valueOf(args(1), 16);
		val end = start + Integer.valueOf(args(2), 16);
		val entryPoint = start + Integer.valueOf(args(3), 16);
		val outf = args(4);
		if((entryPoint-start)%4 != 0){
			start -= 4-((entryPoint-start)%4);
		}
		
		val codes = load(file, start, end);
		val ep = ((entryPoint-start)/4)+1;
		gen(outf, codes, ep);
		println("start: "+Integer.toHexString(start))
		println("end  : "+Integer.toHexString(end))
		println("ep   : "+Integer.toHexString(entryPoint))
		println("base: "+(entryPoint-start))
		println("EntryPoint: "+ep+" / "+codes((entryPoint-start)/4))
	}
}
