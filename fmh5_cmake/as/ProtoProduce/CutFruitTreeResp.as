package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class CutFruitTreeResp
	{
		public static const PROTO:String = "ProtoProduce.CutFruitTreeResp";
		public var package_root:*;
		public  var message:*;
		public var destroyud:int;
		public var commons:CommonItemsCPP;
		public function CutFruitTreeResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			destroyud = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.destroyud = this.destroyud;
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CutFruitTreeResp
		{
			destroyud = undefined;
			commons = undefined;
			this.destroyud = msgObj.destroyud;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CutFruitTreeResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}