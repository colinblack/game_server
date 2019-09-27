package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RecommendllianceReq
	{
		public static const PROTO:String = "ProtoAlliance.RecommendllianceReq";
		public var package_root:*;
		public  var message:*;
		public function RecommendllianceReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):RecommendllianceReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RecommendllianceReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}