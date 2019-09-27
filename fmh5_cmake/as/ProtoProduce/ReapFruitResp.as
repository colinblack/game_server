package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ReapFruitResp
	{
		public static const PROTO:String = "ProtoProduce.ReapFruitResp";
		public var package_root:*;
		public  var message:*;
		public var fruit:FruitCPP;
		public var commons:CommonItemsCPP;
		public function ReapFruitResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			fruit = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.fruit = this.fruit.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReapFruitResp
		{
			fruit = undefined;
			commons = undefined;
			this.fruit = new FruitCPP(package_root).unserialize(msgObj.fruit);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReapFruitResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}