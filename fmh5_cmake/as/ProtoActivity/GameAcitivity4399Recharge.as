package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivity4399Recharge
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivity4399Recharge";
		public var package_root:*;
		public  var message:*;
		public var data:GameAcitivityCPP;
		public function GameAcitivity4399Recharge(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			data = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.data = this.data.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GameAcitivity4399Recharge
		{
			data = undefined;
			this.data = new GameAcitivityCPP(package_root).unserialize(msgObj.data);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivity4399Recharge
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}