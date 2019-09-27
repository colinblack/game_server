package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class GetRotaryTableInfoReq
	{
		public static const PROTO:String = "ProtoRotaryTable.GetRotaryTableInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetRotaryTableInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetRotaryTableInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetRotaryTableInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}