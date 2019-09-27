package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ExitAllianceReq
	{
		public static const PROTO:String = "ProtoAlliance.ExitAllianceReq";
		public var package_root:*;
		public  var message:*;
		public function ExitAllianceReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ExitAllianceReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ExitAllianceReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}