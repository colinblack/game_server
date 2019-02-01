package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BattleCommonCPP
	{
		public static const PROTO:String = "ProtoBattle.BattleCommonCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var propId:Vector.<int>;
		public function BattleCommonCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			propId = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.id!= undefined)
			{
				serializeObj.id = this.id;
			}
			serializeObj.propId = [];
			for(var i:int = 0;i < this.propId.length;i++)
			{
				serializeObj.propId.push(this.propId[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BattleCommonCPP
		{
			id = undefined;
			propId = new Vector.<int>();
			if(msgObj.hasOwnProperty("id"))
			{
				this.id = msgObj.id;
			}
			for(var i:int = 0;i < msgObj.propId.length;i++)
			{
				this.propId.push(msgObj.propId[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BattleCommonCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}