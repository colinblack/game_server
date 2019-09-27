package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class UseCardReq
	{
		public static const PROTO:String = "ProtoActivity.UseCardReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function UseCardReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UseCardReq
		{
			type = undefined;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UseCardReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}