package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ObtainProductReq
	{
		public static const PROTO:String = "ProtoProduce.ObtainProductReq";
		public var package_root:*;
		public  var message:*;
		public var animalud:int;
		public function ObtainProductReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			animalud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.animalud = this.animalud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ObtainProductReq
		{
			animalud = undefined;
			this.animalud = msgObj.animalud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ObtainProductReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}