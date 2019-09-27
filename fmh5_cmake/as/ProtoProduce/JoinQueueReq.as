package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class JoinQueueReq
	{
		public static const PROTO:String = "ProtoProduce.JoinQueueReq";
		public var package_root:*;
		public  var message:*;
		public var propsid:int;
		public var equipud:int;
		public function JoinQueueReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsid = undefined;
			equipud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsid = this.propsid;
			serializeObj.equipud = this.equipud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):JoinQueueReq
		{
			propsid = undefined;
			equipud = undefined;
			this.propsid = msgObj.propsid;
			this.equipud = msgObj.equipud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):JoinQueueReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}