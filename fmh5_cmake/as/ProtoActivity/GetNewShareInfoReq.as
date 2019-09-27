package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GetNewShareInfoReq
	{
		public static const PROTO:String = "ProtoActivity.GetNewShareInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetNewShareInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNewShareInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNewShareInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}