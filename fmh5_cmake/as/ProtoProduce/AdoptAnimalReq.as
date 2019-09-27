package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class AdoptAnimalReq
	{
		public static const PROTO:String = "ProtoProduce.AdoptAnimalReq";
		public var package_root:*;
		public  var message:*;
		public var buildud:int;
		public function AdoptAnimalReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			buildud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.buildud = this.buildud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AdoptAnimalReq
		{
			buildud = undefined;
			this.buildud = msgObj.buildud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AdoptAnimalReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}