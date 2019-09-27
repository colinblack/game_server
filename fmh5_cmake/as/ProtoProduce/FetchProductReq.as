package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class FetchProductReq
	{
		public static const PROTO:String = "ProtoProduce.FetchProductReq";
		public var package_root:*;
		public  var message:*;
		public var pos:int;
		public var equipud:int;
		public function FetchProductReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			pos = undefined;
			equipud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.pos = this.pos;
			serializeObj.equipud = this.equipud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchProductReq
		{
			pos = undefined;
			equipud = undefined;
			this.pos = msgObj.pos;
			this.equipud = msgObj.equipud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchProductReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}