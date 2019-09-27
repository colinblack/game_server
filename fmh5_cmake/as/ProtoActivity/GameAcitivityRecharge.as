package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivityRecharge
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivityRecharge";
		public var package_root:*;
		public  var message:*;
		public var data:GameAcitivityCPP;
		public function GameAcitivityRecharge(root:*)
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
		public function unserialize(msgObj:*):GameAcitivityRecharge
		{
			data = undefined;
			this.data = new GameAcitivityCPP(package_root).unserialize(msgObj.data);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivityRecharge
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}