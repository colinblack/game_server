package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GameAcitivityStatusResp
	{
		public static const PROTO:String = "ProtoActivity.GameAcitivityStatusResp";
		public var package_root:*;
		public  var message:*;
		public var status:int;
		public function GameAcitivityStatusResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.status = this.status;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GameAcitivityStatusResp
		{
			status = undefined;
			this.status = msgObj.status;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GameAcitivityStatusResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}