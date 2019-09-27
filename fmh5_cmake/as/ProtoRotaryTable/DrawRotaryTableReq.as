package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class DrawRotaryTableReq
	{
		public static const PROTO:String = "ProtoRotaryTable.DrawRotaryTableReq";
		public var package_root:*;
		public  var message:*;
		public function DrawRotaryTableReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):DrawRotaryTableReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DrawRotaryTableReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}