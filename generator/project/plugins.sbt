resolvers += Classpaths.typesafeResolver
 
resolvers ++= Seq(
	"snapshots" at "http://oss.sonatype.org/content/repositories/snapshots",
	"typesafe" at "http://repo.typesafe.com/typesafe/releases" 
)

addSbtPlugin("com.eed3si9n" % "sbt-assembly" % "0.10.0")
