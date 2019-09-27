package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPAddProductQueueReq
	{
		public static const PROTO:String = "ProtoVIP.VIPAddProductQueueReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public function VIPAddProductQueueReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPAddProductQueueReq
		{
			ud = undefined;
			this.ud = msgObj.ud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPAddProductQueueReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}