package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ExpandQueueReq
	{
		public static const PROTO:String = "ProtoProduce.ExpandQueueReq";
		public var package_root:*;
		public  var message:*;
		public var equipud:int;
		public function ExpandQueueReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			equipud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.equipud = this.equipud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ExpandQueueReq
		{
			equipud = undefined;
			this.equipud = msgObj.equipud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ExpandQueueReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}