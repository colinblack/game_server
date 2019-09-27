package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivity4399Daily
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivity4399Daily";
		public var package_root:*;
		public  var message:*;
		public var data:GameAcitivityCPP;
		public function GameAcitivity4399Daily(root:*)
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
		public function unserialize(msgObj:*):GameAcitivity4399Daily
		{
			data = undefined;
			this.data = new GameAcitivityCPP(package_root).unserialize(msgObj.data);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivity4399Daily
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}