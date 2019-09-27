package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class ShareReq
	{
		public static const PROTO:String = "ProtoRotaryTable.ShareReq";
		public var package_root:*;
		public  var message:*;
		public function ShareReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShareReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShareReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}