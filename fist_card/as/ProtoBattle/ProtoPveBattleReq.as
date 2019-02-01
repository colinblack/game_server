package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoPveBattleReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoPveBattleReq";
		public var package_root:*;
		public  var message:*;
		public var common:BattleCommonCPP;
		public function ProtoPveBattleReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoPveBattleReq
		{
			common = undefined;
			this.common = new BattleCommonCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoPveBattleReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}