package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSSynOthMartialInfo
	{
		public static const PROTO:String = "ProtoBattle.ProtoCSSynOthMartialInfo";
		public var package_root:*;
		public  var message:*;
		public var othUid:int;
		public var othmGrade:int;
		public var othCoins:int;
		public var othProtectTs:int;
		public var othProps:Vector.<MartialClubProp>;
		public function ProtoCSSynOthMartialInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			othUid = undefined;
			othmGrade = undefined;
			othCoins = undefined;
			othProtectTs = undefined;
			othProps = new Vector.<MartialClubProp>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othUid = this.othUid;
			serializeObj.othmGrade = this.othmGrade;
			serializeObj.othCoins = this.othCoins;
			serializeObj.othProtectTs = this.othProtectTs;
			serializeObj.othProps = [];
			for(var i:int = 0;i < this.othProps.length;i++)
			{
				serializeObj.othProps.push(this.othProps[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSSynOthMartialInfo
		{
			othUid = undefined;
			othmGrade = undefined;
			othCoins = undefined;
			othProtectTs = undefined;
			othProps = new Vector.<MartialClubProp>();
			this.othUid = msgObj.othUid;
			this.othmGrade = msgObj.othmGrade;
			this.othCoins = msgObj.othCoins;
			this.othProtectTs = msgObj.othProtectTs;
			for(var i:int = 0;i < msgObj.othProps.length;i++)
			{
				this.othProps.push(new MartialClubProp(package_root).unserialize(msgObj.othProps[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSSynOthMartialInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}