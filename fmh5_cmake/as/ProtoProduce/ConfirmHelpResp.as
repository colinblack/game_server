package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ConfirmHelpResp
	{
		public static const PROTO:String = "ProtoProduce.ConfirmHelpResp";
		public var package_root:*;
		public  var message:*;
		public var fruit:FruitCPP;
		public function ConfirmHelpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			fruit = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.fruit = this.fruit.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ConfirmHelpResp
		{
			fruit = undefined;
			this.fruit = new FruitCPP(package_root).unserialize(msgObj.fruit);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ConfirmHelpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}